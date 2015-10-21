#include "game.h"

Game Game::instance = Game();

Game& Game::getInstance()
{
	return Game::instance;
}

Game::Game()
{
	this->context = nullptr;
}
Game::~Game()
{
	if (this->context != nullptr)
	{
		this->context->terminate();
		delete this->context;
	}
}

float Game::getDeltaTime()
{
	return this->context->getDeltaTime();
}

ObjectManager& Game::getObjectManager()
{
	return this->objectManager;
}
Context& Game::getContext()
{
	return *this->context;
}

void Game::start()
{
	int width = 800;
	int height = 600;

	// context creation
	this->context = new Context();
	this->context->initialize(4, 3);
	this->context->createWindow(width, height, 1, "ZPG", false, false, true);
	this->context->setKeyCallback([](GLFWwindow* window, int key, int scan, int action, int modifier) { InputController::getInstance().onKeyCallback(window, key, scan, action, modifier); });
	this->context->setMousePositionCallback([](GLFWwindow* window, double x, double y) { InputController::getInstance().onMouseMoveCallback(window, x, y); });
	this->context->setMouseScrollCallback([](GLFWwindow* window, double xOffset, double yOffset) { InputController::getInstance().onMouseScrollCallback(window, xOffset, yOffset); });
	this->context->setMouseButtonCallback([](GLFWwindow* window, int button, int action, int modifier) { InputController::getInstance().onMouseButtonCallback(window, button, action, modifier); });
	this->context->setWindowSizeCallback([](GLFWwindow* window, int width, int height) { Game::getInstance().onWindowSizeCallback(window, width, height); });
	this->context->setShowMouseCursor(false);
	this->context->setDepthTest(true);
	this->context->setStencilTest(true);
	this->context->setCulling(true);
	this->context->setBlending(true);
	this->context->setBlendingFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	this->screenQuad = new ScreenQuad();

	// manager preload
	AudioManager::getInstance().initialize();
	ModelManager::getInstance().preloadModels();
	FontManager::getInstance().initialize(width, height);

	ProgramManager::getInstance().preloadPrograms();
	Program program = ProgramManager::getInstance().get(ProgramManager::PROGRAM_MODEL);
	ProgramManager::getInstance().use(ProgramManager::PROGRAM_MODEL);

	FramebufferManager::getInstance().preloadFramebuffers();

	// initial object spawn
	Camera* cameraScript = new Camera(new CameraController(), glm::vec3(0.0f, 0.0f, -1.0f), 45.0f, 4.0f / 3.0f, 0.1f, 10.0f);
	this->camera = new GameObject(cameraScript);
	this->camera->getTransform().setPosition(glm::vec3(0.0f, 0.0f, 3.5f));

	this->camera->getTags().set(Tag::Camera);
	this->objectManager.add(this->camera);

	IPhysicsComponent* physics = new BasicPhysicsComponent(true, false);
	physics->getForce() = Force(glm::vec3(0.0f, 0.0f, 1.0f), 0.001f);
	GameObject* cube = new GameObject(nullptr, new ModelRenderComponent(ModelManager::getInstance().get(ModelManager::MODEL_NANOSUIT)), physics);
	this->objectManager.add(cube);

	DirectionalLight dirLight;
	dirLight.direction = glm::vec3(50.0f, 50.0f, -100.0f);
	dirLight.phong.diffuse = glm::vec3(1.0f);
	dirLight.phong.ambient = glm::vec3(0.1f);
	dirLight.phong.specular = glm::vec3(1.0f);

	PointLight pointLight;
	pointLight.position = glm::vec3(0.0f, 0.0f, 1.0f);
	pointLight.phong = dirLight.phong;
	pointLight.phong.diffuse = glm::vec3(1.0f, 1.0f, 0.0f);
	pointLight.attenuation = Attenuation(1.0f, 0.09f, 0.032f);

	GameObject* light = new GameObject(new Light<DirectionalLight>(dirLight, "directionalLight"));
	this->objectManager.add(light);
	light = new GameObject(new Light<PointLight>(pointLight, "pointLight"));
	this->objectManager.add(light);

	Timer timer(0.01f);
	Timer gunshotTimer(0.5f);

	context->loop([&](Context& context)	// physics
	{
		this->physicsHandler.simulate(this->objectManager.getObjects(), this->objectManager.getObjectCount(), Context::getFixedDeltaTime());
	},	
	[&](Context& context)	// render
	{
		float delta = context.getDeltaTime();
		timer.update(delta);
		gunshotTimer.update(delta);

		FramebufferManager::getInstance().get(FramebufferManager::FRAMEBUFFER_POSTPROCESS).bind();

		RenderUtils::clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		if (InputController::getInstance().isLeftMouseDown() && gunshotTimer.resetIfReady())
		{
			AudioManager::getInstance().play2DForget("gunshot.wav");
		}

		ProgramManager::getInstance().use(ProgramManager::PROGRAM_MODEL);
		context.setDepthTest(true);

		std::vector<GameObject*> objects = this->objectManager.getObjects();
		size_t objectCount = this->objectManager.getObjectCount();

		for (size_t i = 0; i < objectCount; i++)
		{
			objects[i]->update();
		}

		for (size_t i = 0; i < objectCount; i++)
		{
			objects[i]->draw();
		}

		if (timer.resetIfReady())
		{
			FontManager::getInstance().renderText("FPS: " + std::to_string(round(1.0f / delta)), 10.0f, height - 20.0f, 0.5f, glm::vec3(1.0f, 1.0f, 0.0f));
		}

		this->screenQuad->drawScreen(context);

		if (InputController::getInstance().isButtonPressed(GLFW_KEY_ESCAPE))
		{
			context.closeWindow();
		}

		InputController::getInstance().afterUpdate();
		this->objectManager.removeMarkedObjects();
	});

	// resource disposal
	this->screenQuad->dispose();
	delete this->screenQuad;

	this->objectManager.dispose();
	ProgramManager::getInstance().dispose();
	ModelManager::getInstance().dispose();
	TextureManager::getInstance().dispose();
	FramebufferManager::getInstance().dispose();
	AudioManager::getInstance().dispose();
	FontManager::getInstance().dispose();

	context->terminate();
}

void Game::onWindowSizeCallback(GLFWwindow* window, int width, int height)
{
	this->context->setViewport(0, 0, width, height);

	Camera* camera = (Camera*) this->camera->getScriptComponent();
	camera->setAspect(width / (float) height);

	FontManager::getInstance().setPerspective(width, height);
}