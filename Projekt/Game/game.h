#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "program_manager.h"
#include "timer.h"
#include "Input/input_controller.h"
#include "Component/camera_controller.h"
#include "Physics/transform.h"
#include "../Buffer/vao.h"
#include "../Buffer/vbo.h"
#include "../Context/context.h"
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
	float getDeltaTime();

private:
	static Game instance;

	void onWindowSizeCallback(GLFWwindow* window, int width, int height);

	Context* context;
	Renderer renderer;

	Camera* camera;

	Game();
	~Game();
	Game(const Game& other);
	Game& operator=(const Game& other);
};