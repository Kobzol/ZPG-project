#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <stdexcept>

#include "mouse_state.h"

class InputController
{
	friend class Game;

public:
	static InputController& getInstance();

	bool isButtonPressed(int key);
	bool isLeftMouseDown();
	bool isRightMouseDown();

	MouseState& getMousePosition();
	MouseState& getMouseScroll();

	void afterUpdate();

private:
	static InputController instance;

	InputController();

	void onKeyCallback(GLFWwindow* window, int key, int scan, int action, int modifier);
	void onMouseMoveCallback(GLFWwindow* window, double x, double y);
	void onMouseScrollCallback(GLFWwindow* window, double xOffset, double yOffset);
	void onMouseButtonCallback(GLFWwindow* window, int button, int action, int modifier);

	MouseState mousePosition;
	MouseState mouseScroll;

	int leftMouseDown;
	int rightMouseDown;

	char keys[512];
};