#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class MathHelper
{
public:
	static glm::mat4 rotateAround(const glm::mat4 &origin, float angle, const glm::vec3 axis, const glm::vec3 &point)
	{
		glm::mat4 moveToPoint = glm::translate(origin, point);
		glm::mat4 rotate = glm::rotate(moveToPoint, angle, axis);
		glm::mat4 moveBack = glm::translate(rotate, -point);

		return moveBack;
	}

	static glm::vec3 vectorFromPitchYaw(float pitch, float yaw)
	{
		float pitchRad = glm::radians(pitch);
		float yawRad = glm::radians(yaw);

		float cosPitch = cos(pitchRad);
		float sinPitch = sin(pitchRad);
		float cosYaw = cos(yawRad);
		float sinYaw = sin(yawRad);

		return glm::vec3(cosPitch * cosYaw, sinPitch, cosPitch * sinYaw);

		/*glm::vec3 direction;

		direction.y = sin(glm::radians(pitch));
		direction.x = cos(glm::radians(yaw));
		direction.z = sin(glm::radians(yaw));

		return direction;*/
	}
};