#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <time.h>

#include "scene.h"
#include "screen_quad.h"
#include "tag.h"
#include "timer.h"
#include "Input/input_controller.h"
#include "Camera/camera_controller.h"
#include "Light/directional_light.h"
#include "Light/light_component.h"
#include "Light/point_light.h"
#include "Light/spotlight.h"
#include "Object/object_manager.h"
#include "Physics/basic_physics_component.h"
#include "Physics/physics_handler.h"
#include "Physics/transform.h"
#include "Render/model_render_component.h"
#include "Render/simple_constant_renderer.h"
#include "../Audio/audio_manager.h"
#include "../Buffer/vao.h"
#include "../Buffer/vbo.h"
#include "../Content/framebuffer_manager.h"
#include "../Content/model_manager.h"
#include "../Content/program_manager.h"
#include "../Context/context.h"
#include "../Model/Model.h"
#include "../Model/vertex.h"
#include "../Render/effect_manager.h"
#include "../Render/framebuffer.h"
#include "../Render/program.h"
#include "../Render/render_utils.h"
#include "../Render/shader.h"
#include "../Render/Font/font_manager.h"

class Game
{
public:
	static Game& getInstance();

	void start();
	float getDeltaTime();

	Scene& getActiveScene();
	Context& getContext();

private:
	static Game instance;

	void onWindowSizeCallback(GLFWwindow* window, int width, int height);

	PhysicsHandler physicsHandler;
	Context* context;
	GameObject* camera;
	ScreenQuad* screenQuad;
	Scene scene;

	Game();
	~Game();
	Game(const Game& other);
	Game& operator=(const Game& other);
};