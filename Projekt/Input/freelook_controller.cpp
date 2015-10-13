#include "freelook_controller.h"

FreelookController::FreelookController(float mouseSensitivity) : mouseSensitivity(mouseSensitivity)
{
	this->mousePosOld = glm::vec2(-1.0f, -1.0f);
	this->firstMouseEvent = true;
}

void FreelookController::updateCamera(float delta, Camera& camera)
{
	float diffX = (float) (this->mousePos.x - this->mousePosOld.x);
	float diffY = (float) (this->mousePosOld.y - this->mousePos.y);

	if (diffX != 0 || diffY != 0)
	{
		diffX *= this->mouseSensitivity;
		diffY *= this->mouseSensitivity;

		this->yaw += diffX;
		this->pitch += diffY;

		this->pitch = glm::clamp(this->pitch, -90.0f, 90.0f);

		float pitchRad = glm::radians(this->pitch);
		float yawRad = glm::radians(this->yaw);

		float cosPitch = cos(pitchRad);
		float sinPitch = sin(pitchRad);
		float cosYaw = cos(yawRad);
		float sinYaw = sin(yawRad);
		glm::vec3 cameraFront = glm::vec3(cosPitch * cosYaw, sinPitch, cosPitch * sinYaw);

		camera.setTarget(cameraFront);

		this->mousePosOld = this->mousePos;
	}
}

void FreelookController::setMousePos(double xPos, double yPos)
{
	if (this->firstMouseEvent)
	{
		this->mousePosOld = this->mousePos = glm::vec2(xPos, yPos);
		this->firstMouseEvent = false;

		return;
	}

	this->mousePosOld = this->mousePos;
	this->mousePos = glm::vec2(xPos, yPos);
}
void FreelookController::setLookVector(glm::vec3 lookVector)
{
	lookVector = glm::normalize(lookVector);

	glm::vec3 zeroHorizontalVector = glm::normalize(glm::vec3(1.0f, 0.0f, 0.0f));
	glm::vec3 zeroVerticalVector = glm::normalize(glm::vec3(0.0f, 0.0f, -1.0f));

	float cos = glm::dot(lookVector, zeroHorizontalVector);
	this->yaw = -glm::degrees(acos(cos));

	cos = glm::dot(lookVector, zeroVerticalVector);
	this->pitch = glm::degrees(acos(cos));
}