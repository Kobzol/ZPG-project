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
	memset(this->buttons, 0, sizeof(this->buttons));
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
	this->context->setDepthTest(true);
	this->context->setShowMouseCursor(false);

	Shader vertShader(FileHelper::loadFile("Shaders/Vertex/lambert.vert"), GL_VERTEX_SHADER);
	Shader fragShader(FileHelper::loadFile("Shaders/Fragment/lambert.frag"), GL_FRAGMENT_SHADER);

	Program program;
	program.attachShader(vertShader);
	program.attachShader(fragShader);
	program.link();
	program.use();

	VAO vao;
	vao.bind();

	VBO vbo;
	vbo.bind();
	vbo.setData(VERTICES, sizeof(VERTICES), GL_STATIC_DRAW);

	float angle = 90.0f;
	glm::mat4 model;

	program.setAttribute("position", 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*) offsetof(Vertex, position));
	program.setAttribute("normal", 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*) offsetof(Vertex, normal));

	Camera camera(glm::vec3(0.0f, 0.0f, 3.5f), glm::vec3(0.3f, 0.2f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 45.0f, 4.0f / 3.0f, 0.1f, 10.0f);
	camera.attachListener(&program);
	program.setCameraMatrices(camera);

	this->freelookController.setLookVector(camera.getFront());

	float cameraSpeed = 1.0f;

	context->loop([&](Context& context)
	{
		this->renderer.clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		program.use();

		vao.bind();

		model = glm::rotate(model, glm::radians(10.0f * context.getDeltaTime()), glm::vec3(0.0f, 0.0f, 1.0f));
		program.setUniformMatrix4fv("Model", model);
		program.setUniform4f("color", glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));

		this->renderer.drawTriangles(0, pocetPrvku);

		this->freelookController.updateCamera(context.getDeltaTime(), camera);

		if (this->isButtonPressed(GLFW_KEY_ESCAPE))
		{
			context.closeWindow();
		}
		if (this->isButtonPressed(GLFW_KEY_D))
		{
			camera.move(-camera.getLeft() * cameraSpeed * context.getDeltaTime());
		}
		if (this->isButtonPressed(GLFW_KEY_A))
		{
			camera.move(camera.getLeft() * cameraSpeed * context.getDeltaTime());
		}
		if (this->isButtonPressed(GLFW_KEY_W))
		{
			camera.move(camera.getFront() * cameraSpeed * context.getDeltaTime());
		}
		if (this->isButtonPressed(GLFW_KEY_S))
		{
			camera.move(-camera.getFront() * cameraSpeed * context.getDeltaTime());
		}
	});

	camera.detachListener(&program);

	context->terminate();
}
bool Game::isButtonPressed(int key)
{
	return this->buttons[key] != GLFW_RELEASE;
}

void Game::onKeyCallback(GLFWwindow* window, int key, int scan, int action, int modifier)
{
	this->buttons[key] = action;
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