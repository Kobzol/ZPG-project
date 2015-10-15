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

void Game::start()
{
	this->context = new Context();
	this->context->initialize();
	this->context->createWindow(800, 600, 1, "ZPG", false, false);
	this->context->setKeyCallback([](GLFWwindow* window, int key, int scan, int action, int modifier) { Game::getInstance().onKeyCallback(window, key, scan, action, modifier); });
	this->context->setMousePositionCallback([](GLFWwindow* window, double x, double y) { Game::getInstance().onMouseMoveCallback(window, x, y); });
	this->context->setMouseScrollCallback([](GLFWwindow* window, double xOffset, double yOffset) { Game::getInstance().onMouseScrollCallback(window, xOffset, yOffset); });
	this->context->setMouseButtonCallback([](GLFWwindow* window, int button, int action, int modifier) { Game::getInstance().onMouseButtonCallback(window, button, action, modifier); });
	this->context->setWindowSizeCallback([](GLFWwindow* window, int width, int height) { Game::getInstance().onWindowSizeCallback(window, width, height); });
	this->context->setShowMouseCursor(false);
	this->context->setDepthTest(true);
	this->context->setStencilTest(true);
	this->context->setCulling(true);

	this->camera = new Camera(glm::vec3(0.0f, 0.0f, 3.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 45.0f, 4.0f / 3.0f, 0.1f, 10.0f);

	ProgramManager::getInstance().preloadPrograms();
	Program program = ProgramManager::getInstance().get(ProgramManager::PROGRAM_DEFAULT);
	program.use();

	VAO vao;
	vao.bind();

	VBO vbo;
	vbo.bind();
	vbo.setData(VERTICES, sizeof(VERTICES), GL_STATIC_DRAW);

	program.setAttribute("position", 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*) offsetof(Vertex, position));
	program.setAttribute("normal", 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*) offsetof(Vertex, normal));

	camera->attachListener(&program);
	program.setCameraMatrices(*camera);

	this->freelookController.setLookVector(camera->getFront());

	Transform transform;

	this->context->setStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	Timer timer(0.25f);

	context->loop([&](Context& context)
	{
		float delta = context.getDeltaTime();
		timer.update(delta);

		if (timer.resetIfReady())
		{
			std::cout << "FPS: " << 1.0f / delta << std::endl;
		}

		this->renderer.clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		vao.bind();

		transform.setScale(glm::vec3(1.0f));
		program.setUniformMatrix4fv("Model", transform.getModel());

		EffectManager::getInstance().beforeRender(context);

		program.setUniform4f("color", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
		this->renderer.drawTriangles(0, pocetPrvku);

		EffectManager::getInstance().beforeOutline(context);

		transform.setScale(glm::vec3(1.1f, 1.1f, 1.1f));
		program.setUniformMatrix4fv("Model", transform.getModel());

		program.setUniform4f("color", glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
		this->renderer.drawTriangles(0, pocetPrvku);

		EffectManager::getInstance().afterOutline(context);

		this->freelookController.updateCamera(delta, *camera);
		this->flyController.updateCamera(delta, *camera);

		if (this->flyController.isButtonPressed(GLFW_KEY_ESCAPE))
		{
			glfwSetWindowShouldClose(this->context->getWindow(), 1);
		}
		if (this->flyController.isButtonPressed(GLFW_KEY_RIGHT))
		{
			transform.rotateBy(1.0f * delta, glm::vec3(0.0f, 0.0f, 1.0f));
		}
		if (this->flyController.isButtonPressed(GLFW_KEY_LEFT))
		{
			transform.rotateBy(-1.0f * delta, glm::vec3(0.0f, 0.0f, 1.0f));
		}
	});

	camera->detachListener(&program);
	delete this->camera;

	ProgramManager::getInstance().dispose();

	context->terminate();
}

void Game::onKeyCallback(GLFWwindow* window, int key, int scan, int action, int modifier)
{
	this->flyController.changeButtonState(key, action);
}
void Game::onMouseMoveCallback(GLFWwindow* window, double x, double y)
{
	this->freelookController.setMousePos(x, y);
}
void Game::onMouseScrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{
	this->oldMouseScroll = this->mouseScroll;
	this->mouseScroll = std::make_pair(xOffset, yOffset);
}
void Game::onMouseButtonCallback(GLFWwindow* window, int button, int action, int modifier)
{
	if (button == GLFW_MOUSE_BUTTON_1)
	{
		this->mouseDown.first = action == GLFW_PRESS;
	}
	else if (button == GLFW_MOUSE_BUTTON_2)
	{
		this->mouseDown.second = action == GLFW_PRESS;
	}
}
void Game::onWindowSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);

	this->camera->setAspect(width / (float) height);
}