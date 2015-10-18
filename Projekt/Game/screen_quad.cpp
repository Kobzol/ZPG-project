#include "screen_quad.h"

ScreenQuad::ScreenQuad()
{
	GLfloat quadVertices[] = {
		// Positions   // TexCoords
		-1.0f, 1.0f, 0.0f, 1.0f,
		-1.0f, -1.0f, 0.0f, 0.0f,
		1.0f, -1.0f, 1.0f, 0.0f,

		-1.0f, 1.0f, 0.0f, 1.0f,
		1.0f, -1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 1.0f, 1.0f
	};

	this->vao.bind();
	this->vbo.bind();
	this->vbo.setData(quadVertices, sizeof(quadVertices), GL_STATIC_DRAW);

	Program::setAttribute(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*) 0);	// position
	Program::setAttribute(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*) (sizeof(float) * 2));	// tex coords

	this->vao.unbind();
}

void ScreenQuad::drawScreen(Context& context)
{
	FramebufferManager::getInstance().bindDefault();
	RenderUtils::clearColor(0.0f, 0.0f, 0.0f, 1.0f);
	RenderUtils::clear(GL_COLOR_BUFFER_BIT);

	ProgramManager::getInstance().use(ProgramManager::PROGRAM_POSTPROCESS);

	this->vao.bind();

	context.setDepthTest(false);
	FramebufferManager::getInstance().get(FramebufferManager::FRAMEBUFFER_POSTPROCESS).primaryAttachment.bind(0);
	
	RenderUtils::drawTriangles(0, 6);

	this->vao.unbind();
}

void ScreenQuad::dispose()
{
	this->vao.dispose();
	this->vbo.dispose();
}