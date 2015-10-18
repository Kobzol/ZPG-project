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
	// context creation
	this->context = new Context();
	this->context->initialize(4, 3);
	this->context->createWindow(800, 600, 1, "ZPG", false, false, true);
	this->context->setKeyCallback([](GLFWwindow* window, int key, int scan, int action, int modifier) { InputController::getInstance().onKeyCallback(window, key, scan, action, modifier); });
	this->context->setMousePositionCallback([](GLFWwindow* window, double x, double y) { InputController::getInstance().onMouseMoveCallback(window, x, y); });
	this->context->setMouseScrollCallback([](GLFWwindow* window, double xOffset, double yOffset) { InputController::getInstance().onMouseScrollCallback(window, xOffset, yOffset); });
	this->context->setMouseButtonCallback([](GLFWwindow* window, int button, int action, int modifier) { InputController::getInstance().onMouseButtonCallback(window, button, action, modifier); });
	this->context->setWindowSizeCallback([](GLFWwindow* window, int width, int height) { Game::getInstance().onWindowSizeCallback(window, width, height); });
	this->context->setShowMouseCursor(false);
	this->context->setDepthTest(true);
	this->context->setStencilTest(true);
	this->context->setCulling(true);

	this->screenQuad = new ScreenQuad();

	// manager preload
	ModelManager::getInstance().preloadModels();

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

	GameObject* cube = new GameObject(nullptr, new ModelRenderComponent(ModelManager::getInstance().get(ModelManager::MODEL_CUBE)));
	this->objectManager.add(cube);

	Timer timer(0.25f);

	DirectionalLight light;
	light.direction = glm::vec3(0.0f, 0.0f, 10.0f);
	light.phong.diffuse = glm::vec3(0.3f);
	light.setUniforms(program, "directionalLight");

	// render loop
	context->loop([&](Context& context)
	{
		float delta = context.getDeltaTime();
		timer.update(delta);

		if (timer.resetIfReady())
		{
			//std::cout << "FPS: " << 1.0f / delta << std::endl;
			this->camera->getTransform().rotateBy(1.0f, glm::vec3(0.0f, 0.0f, 1.0f));
		}

		FramebufferManager::getInstance().get(FramebufferManager::FRAMEBUFFER_POSTPROCESS).bind();

		RenderUtils::clearColor(0.0f, 0.0f, 0.0f, 1.0f);
		RenderUtils::clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

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

	context->terminate();
}

void Game::onWindowSizeCallback(GLFWwindow* window, int width, int height)
{
	this->context->setViewport(0, 0, width, height);
	Camera* camera = (Camera*) this->camera->getScriptComponent();
	camera->setAspect(width / (float) height);
}