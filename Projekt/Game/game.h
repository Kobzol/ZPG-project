#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../Buffer/vao.h"
#include "../Buffer/vbo.h"
#include "../Context/context.h"
#include "../Helper/file_helper.h"
#include "../Model/vertex.h"
#include "../Render/shader.h"
#include "../Render/program.h"
#include "../Render/renderer.h"

class Game
{
public:
	static Game& getInstance();

	void start();
	bool isButtonPressed(int key);

	void onKeyCallback(GLFWwindow* window, int key, int scan, int action, int modifier);
	void onMouseMoveCallback(GLFWwindow* window, double x, double y);
	void onMouseScrollCallback(GLFWwindow* window, double xOffset, double yOffset);
	void onMouseButtonCallback(GLFWwindow* window, int button, int action, int modifier);

private:
	static Game instance;

	char buttons[512];

	Context* context;
	Renderer renderer;

	std::pair<GLdouble, GLdouble> oldMousePosition = std::make_pair(-1, -1);
	std::pair<GLdouble, GLdouble> mousePosition = std::make_pair(-1, -1);
	std::pair<GLdouble, GLdouble> oldMouseScroll;
	std::pair<GLdouble, GLdouble> mouseScroll;
	std::pair<bool, bool> mouseDown = std::make_pair(false, false);

	Game();
	~Game();
	Game(const Game& other);
	Game& operator=(const Game& other);
};