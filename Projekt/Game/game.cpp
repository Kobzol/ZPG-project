#include "game.h"

Game Game::instance = Game();

// model selection, shadows, uniform buffer objects

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

Scene& Game::getActiveScene()
{
	return this->scene;
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
	this->context->setDepthFunc(GL_LEQUAL);
	this->context->setStencilTest(true);
	this->context->setStencilMask(0xFF);
	this->context->setStencilFunc(GL_ALWAYS, 1, 0xFF);
	this->context->setStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	this->context->setCulling(true);
	this->context->setBlending(true);
	this->context->setBlendingFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	this->screenQuad = new ScreenQuad();

	// manager preload
	AudioManager::getInstance().initialize();
	TextureManager::getInstance().preloadTextures();
	ModelManager::getInstance().preloadModels();
	FontManager::getInstance().initialize(width, height);
	ProgramManager::getInstance().preloadPrograms();
	Program program = ProgramManager::getInstance().get(ProgramManager::PROGRAM_MODEL);
	ProgramManager::getInstance().use(ProgramManager::PROGRAM_MODEL);

	FramebufferManager::getInstance().preloadFramebuffers();

	// initial object spawn 
	Camera* cameraScript = new Camera(new CameraController(10.0f), glm::vec3(0.0f, 0.0f, -1.0f), 45.0f, 4.0f / 3.0f, 0.1f, 1000.0f);
	this->camera = new GameObject(cameraScript, nullptr, new BasicPhysicsComponent(false, new SphereBoundingBox(1.0f)));
	this->camera->getTransform().setPosition(glm::vec3(0.0f, 0.0f, 8.0f));
	this->camera->getTags().set(Tag::Camera);
	this->scene.add(this->camera);

	ProgramManager::getInstance().observeCamera(cameraScript);

	// objects
	float distance = 3.0f;
	GameObject* cube = new GameObject(nullptr, new ModelRenderComponent(ModelManager::getInstance().get(ModelManager::MODEL_CUBE), Color::Blue));
	this->scene.add(cube);
	cube->getTransform().setPosition(glm::vec3(distance, 0.0f, 0.0f));

	cube = new GameObject(nullptr, new ModelRenderComponent(ModelManager::getInstance().get(ModelManager::MODEL_CUBE), Color::Red));
	this->scene.add(cube);
	cube->getTransform().setPosition(glm::vec3(-distance, 0.0f, 0.0f));

	cube = new GameObject(nullptr, new ModelRenderComponent(ModelManager::getInstance().get(ModelManager::MODEL_CUBE), Color::Green));
	this->scene.add(cube);
	cube->getTransform().setPosition(glm::vec3(0.0f, distance, 0.0f));

	cube = new GameObject(nullptr, new ModelRenderComponent(ModelManager::getInstance().get(ModelManager::MODEL_CUBE), Color::Yellow));
	this->scene.add(cube);
	cube->getTransform().setPosition(glm::vec3(0.0f, -distance, 0.0f));

	// lights
	DirectionalLight *dirLight = new DirectionalLight(glm::vec3(10.0f, 10.0f, 10.0f), Phong(Color::White * 0.001f, Color::White, Color::White * 0.1f));
	GameObject* light = new GameObject(new LightComponent(dirLight, "directionalLight"));
	light->getTags().set(Tag::Light);
	this->scene.add(light);

	PointLight* pointLight = new PointLight(Attenuation::ATT_DISTANCE_LONG, Phong(Color::White * 0.1f, Color::White, Color::White));
	light = new GameObject(
		new LightComponent(pointLight, "pointLights", 0),
		new SimpleConstantRenderer(VERTICES_CUBE, 36, Color::White)
	);
	light->getTransform().setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	light->getTags().set(Tag::Light);
	this->scene.add(light);

	program.setUniform1i("pointLightCount", 1);

	SpotLight* spotLight = new SpotLight(glm::vec3(0.0f, 0.0f, -1.0f), 12.5f, 17.5f, Attenuation::ATT_DISTANCE_LONG, dirLight->phong);
	GameObject* spotLightObj = new GameObject(new LightComponent(spotLight, "spotLight"));
	spotLightObj->getTags().set(Tag::Light);
	this->scene.add(spotLightObj);

	// skybox
	const std::string skyboxPath = "Resources/Textures/skybox/";
	std::vector<Image> skyboxFaces;
	skyboxFaces.push_back(Image(skyboxPath + "right.jpg"));
	skyboxFaces.push_back(Image(skyboxPath + "left.jpg"));
	skyboxFaces.push_back(Image(skyboxPath + "top.jpg"));
	skyboxFaces.push_back(Image(skyboxPath + "bottom.jpg"));
	skyboxFaces.push_back(Image(skyboxPath + "back.jpg"));
	skyboxFaces.push_back(Image(skyboxPath + "front.jpg"));

	Cubemap skyboxCubemap;
	skyboxCubemap.allocate();
	skyboxCubemap.set2DImages(skyboxFaces);

	GameObject* skybox = new GameObject(nullptr, new SkyboxRenderer(skyboxCubemap));
	this->scene.add(skybox);

	GameObject* crossHair = new GameObject(nullptr, new SpriteRenderer(TextureManager::TEXTURE_CROSSHAIR));
	crossHair->getTransform().setScale(glm::vec3(50.0f, 50.0f, 1.0f));
	this->scene.add(crossHair);

	Timer timer(0.01f);
	Timer switchTimer(0.05f);

	context->loop([&](Context& context)	// physics
	{
		//this->physicsHandler.simulate(this->scene.getObjectManager().getObjects(), this->scene.getObjectManager().getObjectCount(), Context::getFixedDeltaTime());
	},	
	[&](Context& context)	// render
	{
		float delta = context.getDeltaTime();
		timer.update(delta);
		switchTimer.update(delta);

		FramebufferManager::getInstance().get(FramebufferManager::FRAMEBUFFER_POSTPROCESS).bind();

		RenderUtils::clearColor(0.0f, 0.0f, 0.0f, 1.0f);
		RenderUtils::clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		context.setDepthTest(true);

		spotLight->direction = cameraScript->getFront();
		spotLightObj->getTransform().setPosition(camera->getTransform().getPosition());

		crossHair->getTransform().setPosition(glm::vec3(context.getWindowWidth() / 2.0f, context.getWindowHeight() / 2.0f, 0.0f));

		this->scene.update();
		this->scene.draw();

		GLchar byte;
		glReadPixels(context.getWindowWidth() / 2, context.getWindowHeight() / 2, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_BYTE, &byte);	// stencil value at the center

		this->screenQuad->drawScreen(context);

		if (timer.resetIfReady())
		{
			FontManager::getInstance().renderText("FPS: " + std::to_string(round(1.0f / delta)), 10.0f, height - 20.0f, 0.5f, glm::vec3(1.0f, 1.0f, 0.0f));
		}

		if (InputController::getInstance().isButtonPressed(GLFW_KEY_ESCAPE))
		{
			context.closeWindow();
		}
		else if (InputController::getInstance().isButtonPressed(GLFW_KEY_SPACE) && switchTimer.resetIfReady())
		{
			// switch render strategy
		}

		InputController::getInstance().afterUpdate();
		
		this->scene.updateFrameEnd();
	});

	// resource disposal
	this->screenQuad->dispose();
	delete this->screenQuad;

	this->scene.dispose();
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