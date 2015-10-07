#include "game.h"

Game Game::instance = Game();

Game& Game::getInstance()
{
	return Game::instance;
}

void Game::start()
{
	Context context;
	context.initialize();
	context.createWindow(800, 600, 1, "ZPG", false, false);
	context.setKeyCallback([](GLFWwindow* window, int key, int scan, int action, int modifier) { Game::getInstance().onKeyCallback(window, key, scan, action, modifier); });
	context.setMousePositionCallback([](GLFWwindow* window, double x, double y) { Game::getInstance().onMouseMoveCallback(window, x, y); });
	context.setMouseScrollCallback([](GLFWwindow* window, double xOffset, double yOffset) { Game::getInstance().onMouseScrollCallback(window, xOffset, yOffset); });
	context.setMouseButtonCallback([](GLFWwindow* window, int button, int action, int modifier) { Game::getInstance().onMouseButtonCallback(window, button, action, modifier); });
}

void Game::onKeyCallback(GLFWwindow* window, int key, int scan, int action, int modifier)
{

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