#pragma once

#include <GL/glew.h>

#include "../Buffer/vao.h"
#include "../Buffer/vbo.h"
#include "../Content/framebuffer_manager.h"
#include "../Content/program_manager.h"
#include "../Context/context.h"
#include "../Render/program.h"
#include "../Render/render_utils.h"

class ScreenQuad
{
public:
	ScreenQuad();

	void drawScreen(Context& context);

	void dispose();

private:
	VAO vao;
	VBO vbo;
};