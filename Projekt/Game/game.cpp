#include "game.h"
#include "models/suzi_flat.h"

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

void Game::start()
{
	this->context = new Context();
	this->context->initialize();
	this->context->createWindow(800, 600, 1, "ZPG", false, false);
	this->context->setKeyCallback([](GLFWwindow* window, int key, int scan, int action, int modifier) { InputController::getInstance().onKeyCallback(window, key, scan, action, modifier); });
	this->context->setMousePositionCallback([](GLFWwindow* window, double x, double y) { InputController::getInstance().onMouseMoveCallback(window, x, y); });
	this->context->setMouseScrollCallback([](GLFWwindow* window, double xOffset, double yOffset) { InputController::getInstance().onMouseScrollCallback(window, xOffset, yOffset); });
	this->context->setMouseButtonCallback([](GLFWwindow* window, int button, int action, int modifier) { InputController::getInstance().onMouseButtonCallback(window, button, action, modifier); });
	this->context->setWindowSizeCallback([](GLFWwindow* window, int width, int height) { Game::getInstance().onWindowSizeCallback(window, width, height); });
	this->context->setShowMouseCursor(false);
	this->context->setDepthTest(true);
	this->context->setStencilTest(true);
	this->context->setCulling(true);

	this->camera = new Camera(new CameraController(), glm::vec3(0.0f, 0.0f, 3.5f), glm::vec3(0.0f, 0.0f, -1.0f), 45.0f, 4.0f / 3.0f, 0.1f, 10.0f);
	this->camera->getTags().set(Tag::Camera);
	this->objectManager.add(this->camera);

	ProgramManager::getInstance().preloadPrograms();
	Program program = ProgramManager::getInstance().get(ProgramManager::PROGRAM_DEFAULT);
	ProgramManager::getInstance().use(ProgramManager::PROGRAM_DEFAULT);

	VAO vao;
	vao.bind();

	VBO vbo;
	vbo.bind();
	vbo.setData(VERTICES, sizeof(VERTICES), GL_STATIC_DRAW);

	program.setAttribute("position", 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*) offsetof(Vertex, position));
	program.setAttribute("normal", 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*) offsetof(Vertex, normal));

	camera->attachListener(&program);
	program.setCameraMatrices(*camera);

	Transform transform;

	this->context->setStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	Timer timer(0.25f);

	context->loop([&](Context& context)
	{
		float delta = context.getDeltaTime();
		timer.update(delta);

		this->camera->update();

		if (timer.resetIfReady())
		{
			std::cout << "FPS: " << 1.0f / delta << std::endl;
			this->camera->rotateBy(1.0f, glm::vec3(0.0f, 0.0f, 1.0f));
		}

		RenderUtils::clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		vao.bind();

		transform.setScale(glm::vec3(1.0f));
		program.setUniformMatrix4fv("Model", transform.getModel());

		EffectManager::getInstance().beforeRender(context);

		program.setUniform4f("color", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
		RenderUtils::drawTriangles(0, (GLsizei)pocetPrvku);

		EffectManager::getInstance().beforeOutline(context);

		transform.setScale(glm::vec3(1.1f, 1.1f, 1.1f));
		program.setUniformMatrix4fv("Model", transform.getModel());

		program.setUniform4f("color", glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
		RenderUtils::drawTriangles(0, (GLsizei)pocetPrvku);

		EffectManager::getInstance().afterOutline(context);

		if (InputController::getInstance().isButtonPressed(GLFW_KEY_ESCAPE))
		{
			glfwSetWindowShouldClose(this->context->getWindow(), 1);
		}

		InputController::getInstance().afterUpdate();
		this->objectManager.removeMarkedObjects();
	});

	this->objectManager.dispose();
	ProgramManager::getInstance().dispose();

	context->terminate();
}

void Game::onWindowSizeCallback(GLFWwindow* window, int width, int height)
{
	this->context->setViewport(0, 0, width, height);
	this->camera->setAspect(width / (float) height);
}