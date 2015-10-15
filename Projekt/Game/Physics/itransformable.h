#pragma once

#include <glm/glm.hpp>

class ITransformable
{
public:
	virtual glm::mat4 getModel() const = 0;

	virtual glm::vec3 getPosition() const = 0;
	virtual glm::quat getRotation() const = 0;
	virtual glm::vec3 getScale() const = 0;

	virtual void setPosition(const glm::vec3 &position) = 0;
	virtual void moveBy(const glm::vec3 &offset) = 0;

	virtual void setRotation(float angle, const glm::vec3 &axis) = 0;
	virtual void rotateBy(float angle, const glm::vec3 &axis) = 0;

	virtual void setScale(const glm::vec3 &scale) = 0;
	virtual void scaleBy(const glm::vec3 &scale) = 0;

	virtual void reset() = 0;
};