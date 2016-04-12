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
Camera* Game::getCamera()
{
	return this->camera;
}
RenderPass Game::getRenderPass()
{
	return this->pass;
}

void Game::start()
{
	int width = 1024;
	int height = 768;

	// context creation
	this->context = new Context();
	this->context->initialize(4, 3);
	this->context->createWindow(width, height, 4, "ZPG", false, false, true);
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
	this->context->setCulling(false);
	this->context->setBlending(true);
	this->context->setBlendingFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	this->context->setMultisampling(true);

	this->screenQuad = new ScreenQuad();

	// manager preload
	AudioManager::getInstance().initialize();
	TextureManager::getInstance().preloadTextures();
	ModelManager::getInstance().preloadModels();
	FontManager::getInstance().initialize(width, height);

	ShaderLoader::getInstance().addCodeMapping("//LIGHT_DEFINITIONS", FileHelper::loadFile("Shaders/Headers/light_definitions.frag"));
	ShaderLoader::getInstance().addCodeMapping("//PHONG_CALCULATIONS", FileHelper::loadFile("Shaders/Headers/phong_calculations.frag"));
	ShaderLoader::getInstance().addCodeMapping("//VERTEX_DATA", FileHelper::loadFile("Shaders/Headers/vertex_data.param"));

	ProgramManager::getInstance().preloadPrograms();
	Program program = ProgramManager::getInstance().get(ProgramManager::PROGRAM_MODEL);
	ProgramManager::getInstance().use(ProgramManager::PROGRAM_MODEL);

	FramebufferManager::getInstance().preloadFramebuffers(width, height);

	// initial object spawn 
	this->camera = new Camera(new CameraController(10.0f), glm::vec3(0.0f, 0.0f, -1.0f), 75.0f, (float) width / height, 0.1f, 1000.0f);
	GameObject* cameraObj = new GameObject(this->camera, new BasicPhysicsComponent(false, new SphereBoundingBox(1.0f)));
	cameraObj->getTransform().setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	cameraObj->getTags().set(Tag::Camera);
	cameraObj->getTransform().setScale(glm::vec3(0.2f));
	this->scene.add(cameraObj);

	ProgramManager::getInstance().observeCamera(this->camera);

	// wall
	GameObject* wall = new GameObject(nullptr, new RenderComponent(Color::White, ProgramManager::PROGRAM_MODEL, new ModelDrawModule("mga/projekt/wall")));
	this->scene.add(wall);
	GameObject* battlements = new GameObject(nullptr, new RenderComponent(Color::White, ProgramManager::PROGRAM_MODEL, new ModelDrawModule("mga/projekt/battlements")));
	this->scene.add(battlements);
	GameObject* gate = new GameObject(nullptr, new RenderComponent(Color::White, ProgramManager::PROGRAM_MODEL, new ModelDrawModule("mga/projekt/gate")));
	this->scene.add(gate);

	// tower
	GameObject* tower = new GameObject(nullptr, new RenderComponent(Color::White, ProgramManager::PROGRAM_MODEL, new ModelDrawModule("mga/projekt/tower")));
	this->scene.add(tower);

	// ground
	GameObject* grass = new GameObject(nullptr, new RenderComponent(Color::White, ProgramManager::PROGRAM_MODEL, new ModelDrawModule("mga/projekt/grass")));
	grass->getTransform().moveBy(glm::vec3(0.0f, 0.05f, 0.0f));
	this->scene.add(grass);

	// gallows
	GameObject* gallows = new GameObject(nullptr, new RenderComponent(Color::White, ProgramManager::PROGRAM_MODEL, new ModelDrawModule("mga/projekt/gallows")));
	this->scene.add(gallows);
	GameObject* chair = new GameObject(nullptr, new RenderComponent(Color::White, ProgramManager::PROGRAM_MODEL, new ModelDrawModule("mga/projekt/chair")));
	this->scene.add(chair);
	GameObject* rope = new GameObject(nullptr, new RenderComponent(Color::White, ProgramManager::PROGRAM_MODEL, new ModelDrawModule("mga/projekt/rope")));
	this->scene.add(rope);
	GameObject* skeleton = new GameObject(nullptr, new RenderComponent(Color::White, ProgramManager::PROGRAM_MODEL, new ModelDrawModule("mga/projekt/skeleton")));
	this->scene.add(skeleton);

	// weapons
	GameObject* weapons = new GameObject(nullptr, new RenderComponent(Color::White, ProgramManager::PROGRAM_MODEL, new ModelDrawModule("mga/projekt/weapons")));
	this->scene.add(weapons);

	// catapult
	GameObject* catapult = new GameObject(nullptr, new RenderComponent(Color::White, ProgramManager::PROGRAM_MODEL, new ModelDrawModule("mga/projekt/catapult")));
	catapult->getTransform().moveBy(glm::vec3(0.0f, 0.08f, 0.0f));
	this->scene.add(catapult);

	// bench
	GameObject* bench = new GameObject(nullptr, new RenderComponent(Color::White, ProgramManager::PROGRAM_MODEL, new ModelDrawModule("mga/projekt/bench")));
	bench->getTransform().moveBy(glm::vec3(0.0f, -0.1f, 0.0f));
	this->scene.add(bench);

	// coins
	GameObject* coins = new GameObject(nullptr, new RenderComponent(Color::White, ProgramManager::PROGRAM_MODEL, new ModelDrawModule("mga/projekt/coins")));
	this->scene.add(coins);

	// crate
	GameObject* crate = new GameObject(nullptr, new RenderComponent(Color::White, ProgramManager::PROGRAM_MODEL, new ModelDrawModule("mga/projekt/crate")));
	this->scene.add(crate);

	// lights
	GeometryObject cubeGeometry(VERTICES_CUBE, sizeof(glm::vec3), 36);
	cubeGeometry.setAttributePosition();

	DirectionalLight *dirLight = new DirectionalLight(Phong(Color::White * 0.001f, Color::White, Color::White * 0.1f));
	GameObject* dirlightObj = new GameObject(
		new LightComponent(dirLight, "directionalLight"));
		//new RenderComponent(Color::White, ProgramManager::PROGRAM_GEOMETRY_CONSTANT, new GeometryDrawModule(cubeGeometry)));
	dirlightObj->getTags().set(Tag::Light);
	dirlightObj->getTransform().setPosition(glm::vec3(0.0f, 40.0f, -20.0f));
	this->scene.add(dirlightObj);

	/*PointLight* pointLight = new PointLight(Attenuation::ATT_DISTANCE_LONG, Phong(Color::White * 0.1f, Color::White * 0.3f, Color::White * 0.2f));
	GameObject* light = new GameObject(
		new LightComponent(pointLight, "pointLights", 0),
		new RenderComponent(Color::White, ProgramManager::PROGRAM_GEOMETRY_CONSTANT, new GeometryDrawModule(cubeGeometry))
	);
	light->getTransform().setPosition(glm::vec3(0.0f, 10.0f, 4.0f));
	light->getTags().set(Tag::Light);
	this->scene.add(light);*/

	program.setUniform1i("pointLightCount", 0);

	SpotLight* spotLight = new SpotLight(glm::vec3(0.0f, 0.0f, -1.0f), 12.5f, 17.5f, Attenuation::ATT_DISTANCE_LONG, dirLight->phong);
	GameObject* spotLightObj = new GameObject(new LightComponent(spotLight, "spotLights", 0));
	spotLightObj->getTags().set(Tag::Light);
	//this->scene.add(spotLightObj);

	program.setUniform1i("spotLightCount", 0);

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

	GameObject* skybox = new GameObject(nullptr, new RenderComponent(Color::White, ProgramManager::PROGRAM_SKYBOX, new SkyboxDrawModule(skyboxCubemap)));
	this->scene.add(skybox);

	GameObject* weaponHUD = new GameObject(new WeaponController(),
		new RenderComponent(Color::White, ProgramManager::PROGRAM_MODEL_NOLIGHT,
		new DecoratorModule(new HUDModule(glm::vec3(0.2f, -0.85f, -1.0f)), new ModelDrawModule("mga/projekt/sword")))
	);
	weaponHUD->getTransform().rotateBy(75.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	weaponHUD->getTransform().rotateBy(75.0f, glm::vec3(0.0f, -1.0f, 0.0f));
	weaponHUD->getTransform().setScale(glm::vec3(1.0f));
	this->scene.add(weaponHUD);

	Timer fpsTimer(0.01f);
	Timer switchTimer(0.5f);
	Timer spawnTimer(10.0f);

	int enableShadows = 1;
	int enableBumpMap = 1;
	int enablePostProcess = 0;
	ProgramManager::getInstance().use(ProgramManager::PROGRAM_MODEL).setUniform1i("useShadows", enableShadows);
	ProgramManager::getInstance().use(ProgramManager::PROGRAM_MODEL).setUniform1i("useBumpMap", enableBumpMap);
	ProgramManager::getInstance().use(ProgramManager::PROGRAM_POSTPROCESS).setUniform1i("postProcess", enablePostProcess);

	const GLuint depthMapTU = 10;
	const size_t maxBulletDistance = 100;

	ObjectManager& objectManager = this->scene.getObjectManager();

	context->loop([&](Context& context)	// physics
	{
		//this->physicsHandler.simulate(objectManager.getObjects(), objectManager.getObjectCount(), Context::getFixedDeltaTime());
		//objectManager.removeMarkedObjects();
	},	
	[&](Context& context)	// render
	{
		float delta = context.getDeltaTime();
		fpsTimer.update(delta);
		switchTimer.update(delta);
		spawnTimer.update(delta);

		spotLight->direction = this->camera->getFront();
		spotLightObj->getTransform().setPosition(this->camera->getGameObject()->getTransform().getPosition());
		
		glm::vec3 normalizedPosition = cameraObj->getTransform().getPosition();
		normalizedPosition.y = 2.0f;
		cameraObj->getTransform().setPosition(normalizedPosition);

		context.setDepthTest(true);

		this->scene.update();
		
		// Shadows
		context.setViewport(0, 0, 4096, 4096);
		Framebuffer& depthBuffer = FramebufferManager::getInstance().get(FramebufferManager::FRAMEBUFFER_DEPTH);
		depthBuffer.bind();
		RenderUtils::clear(GL_DEPTH_BUFFER_BIT);

		glm::mat4 lightProjection = glm::ortho(-100.0f, 100.0f, -100.0f, 100.0f, 1.0f, 200.0f);
		glm::mat4 lightView = glm::lookAt(dirlightObj->getTransform().getPosition(), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4 lightSpaceMatrix = lightProjection * lightView;

		for (auto program : ProgramManager::getInstance().getPrograms())
		{
			if (program.second.getEvents().isSet(ProgramEvent::LightSpace))
			{
				ProgramManager::getInstance().use(program.first);
				program.second.setLightSpaceMatrix(lightSpaceMatrix);
				program.second.setUniform1i("depthMap", depthMapTU);
			}
		}

		Program& depthProgram = ProgramManager::getInstance().use(ProgramManager::PROGRAM_DEPTH);

		ProgramManager::getInstance().lockProgram();
		context.setCullingMode(GL_FRONT);

		this->pass = RenderPass::Depth;
		this->scene.draw();

		context.setCullingMode(GL_BACK);
		ProgramManager::getInstance().unlockProgram();

		// Scene
		context.setViewport(0, 0, context.getWindowWidth(), context.getWindowHeight());
		FramebufferManager::getInstance().get(FramebufferManager::FRAMEBUFFER_POSTPROCESS).bind();

		RenderUtils::clearColor(0.0f, 0.0f, 0.0f, 1.0f);
		RenderUtils::clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		depthBuffer.primaryAttachment.bind(depthMapTU);

		this->pass = RenderPass::Render;
		this->scene.draw();

		this->screenQuad->drawScreen(context);

		size_t objectCount = objectManager.getObjectCount();
		std::vector<GameObject*> &objects = objectManager.getObjects();
		for (size_t i = 0; i < objectCount; i++)
		{
			if (objects[i]->getTags().isSet(Tag::Bullet) && glm::distance(objects[i]->getTransform().getPosition(), glm::vec3(0.0f)) > maxBulletDistance)
			{
				objectManager.markForRemoval(objects[i]);
			}
		}

		if (fpsTimer.resetIfReady())
		{
			//FontManager::getInstance().renderText("FPS: " + std::to_string(round(1.0f / delta)), 10.0f, height - 20.0f, 0.5f, glm::vec3(1.0f, 1.0f, 0.0f));
		}

		if (InputController::getInstance().isButtonPressed(GLFW_KEY_ESCAPE))
		{
			context.closeWindow();
		}
		else if (InputController::getInstance().isButtonPressed(GLFW_KEY_B) && switchTimer.resetIfReady())
		{
			enableShadows = 1 - enableShadows;
			ProgramManager::getInstance().use(ProgramManager::PROGRAM_MODEL).setUniform1i("useShadows", enableShadows);
		}
		else if (InputController::getInstance().isButtonPressed(GLFW_KEY_N) && switchTimer.resetIfReady())
		{
			enableBumpMap = 1 - enableBumpMap;
			ProgramManager::getInstance().use(ProgramManager::PROGRAM_MODEL).setUniform1i("useBumpMap", enableBumpMap);
		}
		else if (InputController::getInstance().isButtonPressed(GLFW_KEY_M) && switchTimer.resetIfReady())
		{
			enablePostProcess = (enablePostProcess + 1) % 3;
			ProgramManager::getInstance().use(ProgramManager::PROGRAM_POSTPROCESS).setUniform1i("postProcess", enablePostProcess);
		}
		/*else if (InputController::getInstance().isButtonPressed(GLFW_KEY_R) && switchTimer.resetIfReady())
		{
			movedObject->getTransform().moveBy(glm::vec3(1.0f, 0.0f, 0.0f));
		}
		else if (InputController::getInstance().isButtonPressed(GLFW_KEY_T) && switchTimer.resetIfReady())
		{
			movedObject->getTransform().moveBy(glm::vec3(-1.0f, 0.0f, 0.0f));
		}
		else if (InputController::getInstance().isButtonPressed(GLFW_KEY_Z) && switchTimer.resetIfReady())
		{
			movedObject->getTransform().moveBy(glm::vec3(0.0f, 0.0f, 1.0f));
		}
		else if (InputController::getInstance().isButtonPressed(GLFW_KEY_U) && switchTimer.resetIfReady())
		{
			movedObject->getTransform().moveBy(glm::vec3(0.0f, 0.0f, -1.0f));
		}*/
		else if (InputController::getInstance().isButtonPressed(GLFW_KEY_K) && switchTimer.resetIfReady())
		{
			SOIL_save_screenshot("screen.bmp", SOIL_SAVE_TYPE_BMP, 0, 0, width, height);
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
	if (width == 0 || height == 0)
	{
		return;
	}

	this->context->setViewport(0, 0, width, height);
	this->context->setWindowSize(width, height);

	this->camera->setAspect(width / (float)height);

	FontManager::getInstance().setPerspective(width, height);
}