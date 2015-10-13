#pragma once

#include <glm/glm.hpp>

#include "../Render/camera.h"

class FreelookController
{
public:
	FreelookController(float mouseSensitivity = 0.05f);

	void updateCamera(float delta, Camera& camera);

	void setLookVector(glm::vec3 lookVector);
	void setMousePos(double xPos, double yPos);

private:
	bool firstMouseEvent;

	glm::vec2 mousePosOld;
	glm::vec2 mousePos;

	float mouseSensitivity;

	float pitch;
	float yaw;
};