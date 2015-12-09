#include "hud_module.h"

void HUDModule::startDraw(RenderComponent* component)
{
	if (Game::getInstance().getRenderPass() == RenderPass::Render)
	{
		Program& program = ProgramManager::getInstance().getCurrentProgram();
		program.setViewMatrix(glm::mat4());
		program.setModelMatrix(glm::mat4(), true);
		RenderUtils::clear(GL_DEPTH_BUFFER_BIT);
	}
}
void HUDModule::endDraw(RenderComponent* component)
{
	if (Game::getInstance().getRenderPass() == RenderPass::Render)
	{
		Program& program = ProgramManager::getInstance().getCurrentProgram();
		program.setViewMatrix(Game::getInstance().getCamera()->calculateViewMatrix());
	}
}