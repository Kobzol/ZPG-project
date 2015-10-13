#include "fly_controller.h"

FlyController::FlyController(float speed) : speed(speed)
{
	memset(this->keys, 0, sizeof(this->keys));	// set GLFW_RELEASE (0) for all keys
}

void FlyController::updateCamera(float delta, Camera& camera)
{
	float actualSpeed = this->speed * delta;

	if (this->isButtonPressed(GLFW_KEY_D))
	{
		camera.move(-camera.getLeft() * actualSpeed);
	}
	if (this->isButtonPressed(GLFW_KEY_A))
	{
		camera.move(camera.getLeft() * actualSpeed);
	}
	if (this->isButtonPressed(GLFW_KEY_W))
	{
		camera.move(camera.getFront() * actualSpeed);
	}
	if (this->isButtonPressed(GLFW_KEY_S))
	{
		camera.move(-camera.getFront() * actualSpeed);
	}
}

void FlyController::changeButtonState(int key, int action)
{
	this->keys[key] = action;
}

bool FlyController::isButtonPressed(int key)
{
	return this->keys[key] != GLFW_RELEASE;
}