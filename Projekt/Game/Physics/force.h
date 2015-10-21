#pragma once

#include <glm/glm.hpp>

#include "transform.h"

class Force
{
public:
	Force(glm::vec3 direction = glm::vec3(), float strength = 0.0f);

	glm::vec3 getDirection();
	float getStrength();

	void applyTo(Transform& transform, float delta);

private:
	glm::vec3 direction;
	float strength;
};