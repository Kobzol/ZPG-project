#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../Context/context.h"

class Game
{
public:
	static Game& getInstance();

	void start();

	void onKeyCallback(GLFWwindow* window, int key, int scan, int action, int modifier);
	void onMouseMoveCallback(GLFWwindow* window, double x, double y);
	void onMouseScrollCallback(GLFWwindow* window, double xOffset, double yOffset);
	void onMouseButtonCallback(GLFWwindow* window, int button, int action, int modifier);

private:
	static Game instance;

	Game() { };
	Game(const Game& other);
	Game& operator=(const Game& other);
};