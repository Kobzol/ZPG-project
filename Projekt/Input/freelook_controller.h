#pragma once

#include <glm/glm.hpp>

#include "../Render/camera.h"

class FreelookController
{
private:
	glm::vec2 mousePosOld;
	glm::vec2 mousePos;

	float mouseSensitivity;

	float pitch;
	float yaw;

	float angleHorizontal = 270.0f;
	float angleVertical = 0.0f;

	float angle = 90.0f;

	float cameraSpeed = 1.0f;

public:
	FreelookController(float mouseSensitivity = 0.05f);

	void updateCamera(float delta, Camera& camera);

	void setMousePos(double xPos, double yPos);
};