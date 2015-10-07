#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace glm {
	glm::mat4 rotateAround(const glm::mat4 &origin, float angle, const glm::vec3 axis, const glm::vec3 &point)
	{
		glm::mat4 moveToPoint = glm::translate(origin, point);
		glm::mat4 rotate = glm::rotate(moveToPoint, angle, axis);
		glm::mat4 moveBack = glm::translate(rotate, -point);

		return moveBack;
	}
}