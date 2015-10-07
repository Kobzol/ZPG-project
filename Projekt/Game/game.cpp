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

void Game::start()
{
	this->context = new Context();
	this->context->initialize();
	this->context->createWindow(800, 600, 1, "ZPG", false, false);
	this->context->setKeyCallback([](GLFWwindow* window, int key, int scan, int action, int modifier) { Game::getInstance().onKeyCallback(window, key, scan, action, modifier); });
	this->context->setMousePositionCallback([](GLFWwindow* window, double x, double y) { Game::getInstance().onMouseMoveCallback(window, x, y); });
	this->context->setMouseScrollCallback([](GLFWwindow* window, double xOffset, double yOffset) { Game::getInstance().onMouseScrollCallback(window, xOffset, yOffset); });
	this->context->setMouseButtonCallback([](GLFWwindow* window, int button, int action, int modifier) { Game::getInstance().onMouseButtonCallback(window, button, action, modifier); });

	Shader vertShader(FileHelper::loadFile("Shaders/Vertex/test.vert"), GL_VERTEX_SHADER);
	Shader fragShader(FileHelper::loadFile("Shaders/Fragment/test.frag"), GL_FRAGMENT_SHADER);

	float points[] = {
		0.0f, 0.0f, 0.0f,	// upper center
		0.5f, -0.5f, 0.0f,	// lower right
		-0.5f, -0.5f, 0.0f,	// lower left
	};

	Program program;
	program.attachShader(vertShader);
	program.attachShader(fragShader);
	program.link();
	program.use();

	VAO vao;
	vao.bind();	

	VBO vbo;
	vbo.bind();
	vbo.setData(points, sizeof(points), GL_STATIC_DRAW);

	float angle = 90.0f;
	glm::mat4 model;

	program.setAttribute("position", 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*) offsetof(Vertex, position));

	Camera camera(glm::vec3(0.0f, 0.0f, 0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 45.0f, 4.0f / 3.0f, 0.1f, 10.0f);
	camera.addListener(&program);
	program.setCameraMatrices(camera);

	context->loop([&](Context& context)
	{
		this->renderer.clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		program.use();

		vao.bind();

		program.setUniformMatrix4fv("Model", model);
		program.setUniform3f("color", glm::vec3(1.0f, 0.0f, 0.0f));

		this->renderer.drawTriangles(0, 3);
	});

	context->terminate();
}

void Game::onKeyCallback(GLFWwindow* window, int key, int scan, int action, int modifier)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		this->context->closeWindow();
	}
}
void Game::onMouseMoveCallback(GLFWwindow* window, double x, double y)
{

}
void Game::onMouseScrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{

}
void Game::onMouseButtonCallback(GLFWwindow* window, int button, int action, int modifier)
{

}