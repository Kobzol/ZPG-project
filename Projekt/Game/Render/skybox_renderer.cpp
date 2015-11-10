#include "skybox_renderer.h"

SkyboxRenderer::SkyboxRenderer(Cubemap cubemap) : cubemap(cubemap)
{
	this->vao.bind();

	this->vbo.bind();
	this->vbo.setData(VERTICES_SKYBOX, 3 * sizeof(float) * 36, GL_STATIC_DRAW);

	Program::setAttribute(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

	this->vao.unbind();
}

void SkyboxRenderer::update()
{
	Program& program = ProgramManager::getInstance().use(ProgramManager::PROGRAM_SKYBOX);

	this->cubemap.bind();
	Context& context = Game::getInstance().getContext();

	this->vao.bind();

	context.setDepthMask(false);
	RenderUtils::drawTriangles(0, 36);
	context.setDepthMask(true);

	this->vao.unbind();
}
void SkyboxRenderer::dispose()
{
	this->vbo.dispose();
	this->vao.dispose();

	this->cubemap.dispose();
}