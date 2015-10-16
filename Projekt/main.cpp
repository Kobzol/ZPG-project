#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Buffer/vbo.h"
#include "Context/context.h"
#include "Game/game.h"
#include "Game/Render/vertex_render_component.h"
#include "Model/vertex.h"
#include "models/suzi_flat.h"

int main()
{
	Game::getInstance().start();

	/*Context* context = new Context();
	context->initialize();
	context->createWindow(800, 600, 1, "ZPG", false, false);

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