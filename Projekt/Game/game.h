#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "tag.h"
#include "timer.h"
#include "Input/input_controller.h"
#include "Component/camera_controller.h"
#include "Content/program_manager.h"
#include "Object/object_manager.h"
#include "Physics/transform.h"
#include "../Buffer/vao.h"
#include "../Buffer/vbo.h"
#include "../Context/context.h"
#include "../Helper/file_helper.h"
#include "../Model/vertex.h"
#include "../Render/effect_manager.h"
#include "../Render/program.h"
#include "../Render/render_utils.h"
#include "../Render/shader.h"

class Game
{
public:
	static Game& getInstance();

	void start();
	float getDeltaTime();

	ObjectManager& getObjectManager();

private:
	static Game instance;

	void onWindowSizeCallback(GLFWwindow* window, int width, int height);

	ObjectManager objectManager;
	Context* context;
	Camera* camera;

	Game();
	~Game();
	Game(const Game& other);
	Game& operator=(const Game& other);
};