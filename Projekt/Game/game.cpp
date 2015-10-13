#include "game.h"

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

	Shader vertShader(FileHelper::loadFile("Shaders/Vertex/model.vert"), GL_VERTEX_SHADER);
	Shader fragShader(FileHelper::loadFile("Shaders/Fragment/model.frag"), GL_FRAGMENT_SHADER);

	Program program;
	program.attachShader(vertShader);
	program.attachShader(fragShader);
	program.link();
	program.use();

	double xpos_old = -1;
	double ypos_old = -1;

	GLfloat pitch = 0.0f;
	GLfloat yaw = -90.0f;
	GLfloat mouseSensitivity = 0.05f;

	float angleHorizontal = 270.0f;
	float angleVertical = 0.0f;

	float angle = 90.0f;
	glm::mat4 model;

	Camera camera(glm::vec3(0.0f, 0.0f, 0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
	camera.attachListener(&program);
	program.setCameraMatrices(camera);

	float cameraSpeed = 1.0f;
	float mouseX, mouseY;

	Model modelObject("nanosuit/nanosuit.obj");

	context->loop([&](Context& context)
	{
		this->renderer.clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		program.use();

		model = glm::rotate(model, glm::radians(10.0f * context.getDeltaTime()), glm::vec3(0.0f, 0.0f, 1.0f));
		program.setUniformMatrix4fv("Model", model);

		modelObject.draw(program, this->renderer);

		double diffX = this->mousePosition.first - this->oldMousePosition.first;
		double diffY = this->oldMousePosition.second - this->mousePosition.second;

		if (diffX != 0 || diffY != 0)
		{
			diffX *= mouseSensitivity;
			diffY *= mouseSensitivity;

			yaw += (GLfloat) diffX;
			pitch += (GLfloat) diffY;

			pitch = glm::clamp(pitch, -89.0f, 89.0f);

			GLfloat cosPitch = cos(glm::radians(pitch));
			GLfloat sinPitch = sin(glm::radians(pitch));
			GLfloat cosYaw = cos(glm::radians(yaw));
			GLfloat sinYaw = sin(glm::radians(yaw));
			glm::vec3 cameraFront = glm::vec3(cosPitch * cosYaw, sinPitch, cosPitch * sinYaw);

			camera.setTarget(cameraFront);

			this->oldMousePosition = this->mousePosition;
		}

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
	if (this->oldMousePosition.first == -1)	// first mouse move
	{
		this->oldMousePosition = this->mousePosition = std::make_pair(x, y);
	}
	else
	{
		this->oldMousePosition = this->mousePosition;
		this->mousePosition = std::make_pair(x, y);
	}
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