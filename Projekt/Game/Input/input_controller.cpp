#include "input_controller.h"

InputController InputController::instance = InputController();

InputController& InputController::getInstance()
{
	return InputController::instance;
}

InputController::InputController()
{
	memset(this->keys, 0, sizeof(this->keys));	// set GLFW_RELEASE (0) for all keys
}

bool InputController::isButtonPressed(int key)
{
	if (key < 0 || key >= 512)
	{
		throw std::range_error("Key doesn't exist");
	}

	return this->keys[key] != GLFW_RELEASE;
}
bool InputController::isLeftMouseDown()
{
	return this->leftMouseDown == GLFW_PRESS;
}
bool InputController::isRightMouseDown()
{
	return this->rightMouseDown == GLFW_PRESS;
}

MouseState& InputController::getMousePosition()
{
	return this->mousePosition;
}
MouseState& InputController::getMouseScroll()
{
	return this->mouseScroll;
}

void InputController::afterUpdate()
{
	this->mousePosition.resetOldState();
	this->mouseScroll.resetOldState();
}

void InputController::onKeyCallback(GLFWwindow* window, int key, int scan, int action, int modifier)
{
	this->keys[key] = action;
}
void InputController::onMouseMoveCallback(GLFWwindow* window, double x, double y)
{
	this->mousePosition.update((float) x, (float) y);
}
void InputController::onMouseScrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{
	this->mouseScroll.update((float) xOffset, (float) yOffset);
}
void InputController::onMouseButtonCallback(GLFWwindow* window, int button, int action, int modifier)
{
	if (button == GLFW_MOUSE_BUTTON_1)
	{
		this->leftMouseDown = action;
	}
	else if (button == GLFW_MOUSE_BUTTON_2)
	{
		this->rightMouseDown = action;
	}
}