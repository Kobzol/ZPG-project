#include "hud_module.h"

HUDModule::HUDModule(glm::vec3 position) : position(position)
{

}

void HUDModule::startDraw(RenderComponent* component)
{
	if (Game::getInstance().getRenderPass() == RenderPass::Render)
	{
		Program& program = ProgramManager::getInstance().getCurrentProgram();
		program.setViewMatrix(glm::mat4());

		GameObject* obj = component->getGameObject();
		obj->getTransform().setPosition(this->position);

		program.setModelMatrix(obj->getTransform().getModel(), true);
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