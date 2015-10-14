#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "program_manager.h"
#include "Physics/transform.h"
#include "../Buffer/vao.h"
#include "../Buffer/vbo.h"
#include "../Context/context.h"
#include "../Input/fly_controller.h"
#include "../Input/freelook_controller.h"
#include "../Helper/file_helper.h"
#include "../Model/vertex.h"
#include "../Render/effect_manager.h"
#include "../Render/program.h"
#include "../Render/renderer.h"
#include "../Render/shader.h"

class Game
{
public:
	static Game& getInstance();

	void start();

	void onKeyCallback(GLFWwindow* window, int key, int scan, int action, int modifier);
	void onMouseMoveCallback(GLFWwindow* window, double x, double y);
	void onMouseScrollCallback(GLFWwindow* window, double xOffset, double yOffset);
	void onMouseButtonCallback(GLFWwindow* window, int button, int action, int modifier);
	void onWindowSizeCallback(GLFWwindow* window, int width, int height);

private:
	static Game instance;

	Context* context;
	Renderer renderer;

	Camera* camera;

	FreelookController freelookController;
	FlyController flyController;

	std::pair<GLdouble, GLdouble> oldMouseScroll;
	std::pair<GLdouble, GLdouble> mouseScroll;
	std::pair<bool, bool> mouseDown = std::make_pair(false, false);

	Game();
	~Game();
	Game(const Game& other);
	Game& operator=(const Game& other);
};