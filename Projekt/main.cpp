#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Buffer/vbo.h"
#include "Context/context.h"
#include "Game/game.h"
#include "Model/vertex.h"

int main()
{
	Game::getInstance().start();

	/*Context* context = new Context();
	context->initialize(4, 5);
	context->createWindow(800, 600, 1, "ZPG", false, false);

	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
	printf("Vendor %s\n", glGetString(GL_VENDOR));
	printf("Renderer %s\n", glGetString(GL_RENDERER));
	printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	int major, minor, revision;
	glfwGetVersion(&major, &minor, &revision);
	printf("Using GLFW %i.%i.%i\n", major, minor, revision);

	ProgramManager::getInstance().preloadPrograms();
	Program program = ProgramManager::getInstance().get(ProgramManager::PROGRAM_DEFAULT);
	ProgramManager::getInstance().use(ProgramManager::PROGRAM_DEFAULT);

	VertexRenderComponent* vrc = new VertexRenderComponent(VERTICES, (size_t) pocetPrvku);

	int i = 0;
	context->loop([&](Context& context)
	{
		vrc->update();
		i++;

		if (i == 100)
		{
			context.closeWindow();
		}
	});

	vrc->dispose();
	delete vrc;

	context->terminate();
	delete context;*/

	return 0;
}