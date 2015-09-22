#include "camera.h"

Camera::Camera(
	glm::vec3 position, glm::vec3 target, glm::vec3 up,
	float fov, float aspect, float nearPlane, float farPlane
	) : position(position), target(target), up(up),
		fov(fov), aspect(aspect), nearPlane(nearPlane), farPlane(farPlane)
{
	this->recalculateViewMatrix();
	this->recalculateProjectionMatrix();
}

void Camera::recalculateViewMatrix()
{
	this->viewMatrix = glm::lookAt(
		this->position,
		this->target,
		this->up
	);
}
void Camera::recalculateProjectionMatrix()
{
	this->projectionMatrix = glm::perspective(
		this->fov,
		this->aspect,
		this->nearPlane,
		this->farPlane
	);
}

void Camera::setPosition(glm::vec3 position)
{
	this->position = position;
	this->recalculateViewMatrix();
}
void Camera::setTarget(glm::vec3 target)
{
	this->target = target;
	this->recalculateViewMatrix();
}
void Camera::setUpVector(glm::vec3 up)
{
	this->up = up;
	this->recalculateViewMatrix();
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