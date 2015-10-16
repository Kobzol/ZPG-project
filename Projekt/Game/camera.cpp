#include "camera.h"

Camera::Camera(
	IScriptComponent* controller,
	glm::vec3 target,
	float fov, float aspect, float nearPlane, float farPlane
	) : controller(controller), target(target), fov(fov), aspect(aspect), nearPlane(nearPlane), farPlane(farPlane), perspectiveDirty(true)
{
	
}

void Camera::update()
{
	Program& program = ProgramManager::getInstance().getCurrentProgram();

	if (this->perspectiveDirty)
	{
		program.setProjectionMatrix(this->calculateProjectionMatrix());
		this->perspectiveDirty = false;
	}
	if (this->gameObject->getTransform().isDirty({ TransformDirtyBit::Position, TransformDirtyBit::Rotation }))
	{
		program.setViewMatrix(this->calculateViewMatrix());
	}

	if (this->controller != nullptr)
	{
		this->controller->update();
	}
}
void Camera::setGameObject(GameObject* object)
{
	IScriptComponent::setGameObject(object);

	if (this->controller != nullptr)
	{
		this->controller->setGameObject(object);
	}
}

glm::mat4 Camera::calculateViewMatrix()
{
	return glm::lookAt(
		this->gameObject->getTransform().getPosition(),
		this->gameObject->getTransform().getPosition() + this->target,
		this->getUp()
	);
}
glm::mat4 Camera::calculateProjectionMatrix()
{
	return glm::perspective(
		this->fov,
		this->aspect,
		this->nearPlane,
		this->farPlane
	);
}

void Camera::setTarget(glm::vec3 target)
{
	this->target = glm::normalize(target);
}

glm::vec3 Camera::getLeft()
{
	return glm::normalize(glm::cross(this->getUp(), this->target));
}
glm::vec3 Camera::getUp()
{
	return glm::vec3(0.0f, 1.0f, 0.0f) * this->gameObject->getTransform().getRotation();
}
glm::vec3 Camera::getFront()
{
	return glm::normalize(this->target);
}

void Camera::setFov(float fov)
{
	this->fov = fov;
	this->perspectiveDirty = true;
}
void Camera::setAspect(float aspect)
{
	this->aspect = aspect;
	this->perspectiveDirty = true;
}
void Camera::setNearPlane(float nearPlane)
{
	this->nearPlane = nearPlane;
	this->perspectiveDirty = true;
}
void Camera::setFarPlane(float farPlane)
{
	this->farPlane = farPlane;
	this->perspectiveDirty = true;
}

void Camera::dispose()
{
	this->controller->dispose();
	delete this->controller;
}