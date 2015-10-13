#pragma once

#include <GLFW/glfw3.h>

#include <memory>

#include "../Render/camera.h"

class FlyController
{
public:
	FlyController(float speed = 1.0f);

	void updateCamera(float delta, Camera& camera);

	void changeButtonState(int key, int action);

	bool isButtonPressed(int key);

private:
	float speed;
	char keys[512];
};