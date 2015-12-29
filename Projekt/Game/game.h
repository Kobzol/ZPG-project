#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/gtc/noise.hpp>

#include <time.h>
#include <random>

#include "heightmap.h"
#include "scene.h"
#include "screen_quad.h"
#include "tag.h"
#include "timer.h"
#include "weapon_controller.h"
#include "Input/input_controller.h"
#include "Camera/camera_controller.h"
#include "Light/directional_light.h"
#include "Light/light_component.h"
#include "Light/point_light.h"
#include "Light/spotlight.h"
#include "Object/object_manager.h"
#include "Path/bezier_path_handler.h"
#include "Path/ipath_handler.h"
#include "Path/linear_path_handler.h"
#include "Path/path_follower.h"
#include "Physics/basic_physics_component.h"
#include "Physics/physics_handler.h"
#include "Render/render_component.h"
#include "Render/render_pass.h"
#include "Render/Module/decorator_module.h"
#include "Render/Module/geometry_draw_module.h"
#include "Render/Module/hud_module.h"
#include "Render/Module/model_draw_module.h"
#include "Render/Module/outline_module.h"
#include "Render/Module/skybox_draw_module.h"
#include "Render/Module/sprite_draw_module.h"
#include "../Audio/audio_manager.h"
#include "../Content/framebuffer_manager.h"
#include "../Content/model_manager.h"
#include "../Content/program_manager.h"
#include "../Context/context.h"
#include "../Helper/file_helper.h"
#include "../Model/Model.h"
#include "../Model/vertex.h"
#include "../Render/color.h"
#include "../Render/framebuffer.h"
#include "../Render/program.h"
#include "../Render/Font/font_manager.h"

class Game
{
public:
	static Game& getInstance();

	void start();
	float getDeltaTime();
	Camera* getCamera();
	RenderPass getRenderPass();

	Scene& getActiveScene();
	Context& getContext();

private:
	static Game instance;

	void onWindowSizeCallback(GLFWwindow* window, int width, int height);

	PhysicsHandler physicsHandler;
	Context* context;
	Camera* camera;
	ScreenQuad* screenQuad;
	Scene scene;
	RenderPass pass;

	Game();
	~Game();
	Game(const Game& other);
	Game& operator=(const Game& other);
};