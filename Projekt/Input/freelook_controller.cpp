#include "freelook_controller.h"

FreelookController::FreelookController(float mouseSensitivity) : mouseSensitivity(mouseSensitivity)
{
	this->mousePosOld = glm::vec2(-1.0f, -1.0f);
	this->yaw = -90.0f;
}

void FreelookController::update(double xPos, double yPos, float delta, Camera& camera)
{
	if (this->mousePosOld.x == -1.0f)
	{
		this->mousePosOld.x = (float) xPos;
		this->mousePosOld.y = (float) yPos;

		return;
	}

	float diffX = (float) (xPos - this->mousePosOld.x);
	float diffY = (float) (this->mousePosOld.y - yPos);

	this->mousePosOld.x = (float) xPos;
	this->mousePosOld.y = (float) yPos;

	if (diffX != 0 || diffY != 0)
	{
		diffX *= this->mouseSensitivity;
		diffY *= this->mouseSensitivity;

		this->yaw += diffX;
		this->pitch += diffY;

		this->pitch = glm::clamp(this->pitch, -89.0f, 89.0f);

		float cosPitch = cos(glm::radians(this->pitch));
		float sinPitch = sin(glm::radians(this->pitch));
		float cosYaw = cos(glm::radians(this->yaw));
		float sinYaw = sin(glm::radians(this->yaw));
		glm::vec3 cameraFront = glm::vec3(cosPitch * cosYaw, sinPitch, cosPitch * sinYaw);

		camera.setTarget(cameraFront);
	}
}