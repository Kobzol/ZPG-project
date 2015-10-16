#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

#include "../../Helper/flags.h"

enum class TransformDirtyBit
{
	Position = 1,
	Rotation = 2,
	Scale = 3
};

class Transform
{
public:
	Transform(const glm::vec3 &position = glm::vec3(0.0f),
			  const glm::vec3 &rotation = glm::vec3(0.0f),
			  const glm::vec3 &scale = glm::vec3(1.0f));

	glm::mat4 getModel() const;

	glm::vec3 getPosition() const;
	glm::quat getRotation() const;
	glm::vec3 getScale() const;

	void setPosition(const glm::vec3 &position);
	void moveBy(const glm::vec3 &offset);

	void setRotation(float angle, const glm::vec3 &axis);
	void rotateBy(float angle, const glm::vec3 &axis);

	void setScale(const glm::vec3 &scale);
	void scaleBy(const glm::vec3 &scale);

	bool isDirty(std::initializer_list<TransformDirtyBit> bits);
	void clearDirty(std::initializer_list<TransformDirtyBit> bits);

	void reset();

private:
	void setDirty(std::initializer_list<TransformDirtyBit> bits);

	glm::vec3 position;
	glm::vec3 scale;
	glm::quat quat;

	Flags<TransformDirtyBit> dirty;
};