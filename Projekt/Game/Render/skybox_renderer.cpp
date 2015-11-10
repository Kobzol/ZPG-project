#include "skybox_renderer.h"

SkyboxRenderer::SkyboxRenderer(Cubemap cubemap) : cubemap(cubemap)
{
	this->geometryObject.setGeometry(VERTICES_SKYBOX, 3 * sizeof(float), 36);
	this->geometryObject.setAttributePosition();
}

void SkyboxRenderer::update()
{
	Program& program = ProgramManager::getInstance().use(ProgramManager::PROGRAM_SKYBOX);

	this->cubemap.bind();
	Context& context = Game::getInstance().getContext();

	this->geometryObject.getVAO().bind();

	context.setDepthMask(false);
	RenderUtils::drawTriangles(0, 36);
	context.setDepthMask(true);

	this->geometryObject.getVAO().unbind();
}
void SkyboxRenderer::dispose()
{
	this->geometryObject.dispose();
	this->cubemap.dispose();
}