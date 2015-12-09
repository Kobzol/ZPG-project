#include "skybox_draw_module.h"

SkyboxDrawModule::SkyboxDrawModule(Cubemap cubemap) : cubemap(cubemap)
{
	this->geometry.setGeometry(VERTICES_SKYBOX, 3 * sizeof(float), 36);
	this->geometry.setAttributePosition();
}

void SkyboxDrawModule::startDraw(RenderComponent* component)
{
	Context& context = Game::getInstance().getContext();

	this->cubemap.bind();
	this->geometry.getVAO().bind();

	context.setDepthMask(false);
	RenderUtils::drawTriangles(0, 36);
	context.setDepthMask(true);

	this->geometry.getVAO().unbind();
}
void SkyboxDrawModule::dispose()
{
	this->geometry.dispose();
	this->cubemap.dispose();
}