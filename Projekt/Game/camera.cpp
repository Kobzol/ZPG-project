#include "camera.h"

Camera::Camera(
	IScriptComponent* controller,
	glm::vec3 target,
	float fov, float aspect, float nearPlane, float farPlane
	) : controller(controller), target(target), fov(fov), aspect(aspect), nearPlane(nearPlane), farPlane(farPlane)
{
	this->setDirty({ CameraDirtyBit::Perspective, CameraDirtyBit::Target });
}

void Camera::update()
{
	Program& program = ProgramManager::getInstance().getCurrentProgram();

	if (this->isDirty({ CameraDirtyBit::Perspective }))
	{
		program.setProjectionMatrix(this->calculateProjectionMatrix());
		this->clearDirty({ CameraDirtyBit::Perspective });
	}
	if (this->gameObject->getTransform().isDirty({ TransformDirtyBit::Position }) ||
		this->gameObject->getTransform().isDirty({ TransformDirtyBit::Rotation }) ||
		this->isDirty({ CameraDirtyBit::Target }))
	{
		program.setViewMatrix(this->calculateViewMatrix());
		this->gameObject->getTransform().clearDirty({ TransformDirtyBit::Position, TransformDirtyBit::Rotation });
		this->clearDirty({ CameraDirtyBit::Target });
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
	this->setDirty({ CameraDirtyBit::Target });
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
	this->setDirty({ CameraDirtyBit::Perspective });
}
void Camera::setAspect(float aspect)
{
	this->aspect = aspect;
	this->setDirty({ CameraDirtyBit::Perspective });
}
void Camera::setNearPlane(float nearPlane)
{
	this->nearPlane = nearPlane;
	this->setDirty({ CameraDirtyBit::Perspective });
}
void Camera::setFarPlane(float farPlane)
{
	this->farPlane = farPlane;
	this->setDirty({ CameraDirtyBit::Perspective });
}

void Camera::dispose()
{
	this->controller->dispose();
	delete this->controller;
}

bool Camera::isDirty(std::initializer_list<CameraDirtyBit> bits)
{
	return this->dirty.isSet(bits);
}
void Camera::clearDirty(std::initializer_list<CameraDirtyBit> bits)
{
	this->dirty.unset(bits);
}
void Camera::setDirty(std::initializer_list<CameraDirtyBit> bits)
{
	this->dirty.set(bits);
}