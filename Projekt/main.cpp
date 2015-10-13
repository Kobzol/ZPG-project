#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Game/game.h"

int main()
{
	Game::getInstance().start();

	return 0;
}