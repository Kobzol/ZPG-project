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

public:
	FreelookController(float mouseSensitivity = 0.05f);

	void updateCamera(float delta, Camera& camera);

	void setMousePos(double xPos, double yPos);
};