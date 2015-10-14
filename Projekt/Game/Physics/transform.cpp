#include "transform.h"

Transform::Transform(const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec3 &scale) : position(position), quat(rotation), scale(scale)
{

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
}
void Transform::moveBy(const glm::vec3 &offset)
{
	this->position += offset;
}

void Transform::setRotation(float angle, const glm::vec3 &axis)
{
	this->quat = glm::rotate(glm::quat(), angle, axis);
}
void Transform::rotateBy(float angle, const glm::vec3 &axis)
{
	this->quat = glm::rotate(quat, angle, axis);
}

void Transform::setScale(const glm::vec3 &scale)
{
	this->scale = scale;
}
void Transform::scaleBy(const glm::vec3 &scale)
{
	this->scale *= scale;
}

void Transform::reset()
{
	this->position = glm::vec3(0.0f);
	this->scale = glm::vec3(1.0f);
	this->quat = glm::quat();
}