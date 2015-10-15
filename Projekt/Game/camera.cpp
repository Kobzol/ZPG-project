#include "camera.h"

Camera::Camera(
	IScriptComponent* component,
	glm::vec3 position, glm::vec3 target, glm::vec3 up,
	float fov, float aspect, float nearPlane, float farPlane
	) : target(target), up(up),
	fov(fov), aspect(aspect), nearPlane(nearPlane), farPlane(farPlane), GameObject(component)
{
	this->setPosition(position);

	this->recalculateViewMatrix();
	this->recalculateProjectionMatrix();

	this->broadcaster.setCallback([this](EventListener* listener)
	{
		CameraChangedListener* list = (CameraChangedListener*) listener;
		list->notifyCameraChanged(*this);
	});
}

void Camera::recalculateViewMatrix()
{
	this->viewMatrix = glm::lookAt(
		this->getPosition(),
		this->getPosition() + this->target,
		this->up
	);
	this->broadcaster.notify();
}
void Camera::recalculateProjectionMatrix()
{
	this->projectionMatrix = glm::perspective(
		this->fov,
		this->aspect,
		this->nearPlane,
		this->farPlane
	);
	this->broadcaster.notify();
}

void Camera::setPosition(const glm::vec3& position)
{
	GameObject::setPosition(position);
	this->recalculateViewMatrix();
}
void Camera::moveBy(const glm::vec3& offset)
{
	GameObject::moveBy(offset);
	this->recalculateViewMatrix();
}
void Camera::setTarget(glm::vec3 target)
{
	this->target = glm::normalize(target);
	this->recalculateViewMatrix();
}
void Camera::setUpVector(glm::vec3 up)
{
	this->up = up;
	this->recalculateViewMatrix();
}

glm::vec3 Camera::getLeft()
{
	return glm::normalize(glm::cross(this->up, this->target));
}
glm::vec3 Camera::getFront()
{
	return glm::normalize(this->target);
}

void Camera::setFov(float fov)
{
	this->fov = fov;
	this->recalculateProjectionMatrix();
}
void Camera::setAspect(float aspect)
{
	this->aspect = aspect;
	this->recalculateProjectionMatrix();
}
void Camera::setNearPlane(float nearPlane)
{
	this->nearPlane = nearPlane;
	this->recalculateProjectionMatrix();
}
void Camera::setFarPlane(float farPlane)
{
	this->farPlane = farPlane;
	this->recalculateProjectionMatrix();
}

glm::mat4 Camera::getViewMatrix()
{
	return this->viewMatrix;
}
glm::mat4 Camera::getProjectionMatrix()
{
	return this->projectionMatrix;
}

void Camera::attachListener(CameraChangedListener* listener)
{
	this->broadcaster.attachListener(listener);
}
void Camera::detachListener(CameraChangedListener* listener)
{
	this->broadcaster.detachListener(listener);
}