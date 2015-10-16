#include "transform.h"

Transform::Transform(const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec3 &scale) : position(position), quat(rotation), scale(scale)
{
	this->setDirty({ TransformDirtyBit::Position, TransformDirtyBit::Rotation, TransformDirtyBit::Scale });
}

glm::mat4 Transform::getModel() const
{
	glm::mat4 model;
	model = glm::translate(model, this->position);
	model *= glm::mat4_cast(this->quat);
	model = glm::scale(model, this->scale);

	return model;
}

glm::vec3 Transform::getPosition() const
{
	return this->position;
}
glm::quat Transform::getRotation() const
{
	return this->quat;
}
glm::vec3 Transform::getScale() const
{
	return this->scale;
}

void Transform::setPosition(const glm::vec3 &position)
{
	this->position = position;
	this->setDirty({ TransformDirtyBit::Position });
}
void Transform::moveBy(const glm::vec3 &offset)
{
	this->position += offset;
	this->setDirty({ TransformDirtyBit::Position });
}

void Transform::setRotation(float angle, const glm::vec3 &axis)
{
	this->quat = glm::rotate(glm::quat(), glm::radians(angle), axis);
	this->setDirty({ TransformDirtyBit::Rotation });
}
void Transform::rotateBy(float angle, const glm::vec3 &axis)
{
	this->quat = glm::rotate(quat, glm::radians(angle), axis);
	this->setDirty({ TransformDirtyBit::Rotation });
}

void Transform::setScale(const glm::vec3 &scale)
{
	this->scale = scale;
	this->setDirty({ TransformDirtyBit::Scale });
}
void Transform::scaleBy(const glm::vec3 &scale)
{
	this->scale *= scale;
	this->setDirty({ TransformDirtyBit::Scale });
}

bool Transform::isDirty()
{
	return !this->dirty.isZero();
}
bool Transform::isDirty(std::initializer_list<TransformDirtyBit> bits)
{
	return this->dirty.isSet(bits);
}
void Transform::clearDirty(std::initializer_list<TransformDirtyBit> bits)
{
	this->dirty.unset(bits);
}

void Transform::reset()
{
	this->position = glm::vec3(0.0f);
	this->scale = glm::vec3(1.0f);
	this->quat = glm::quat();

	this->setDirty({ TransformDirtyBit::Position, TransformDirtyBit::Rotation, TransformDirtyBit::Scale });
}

void Transform::setDirty(std::initializer_list<TransformDirtyBit> bits)
{
	this->dirty.set(bits);
}