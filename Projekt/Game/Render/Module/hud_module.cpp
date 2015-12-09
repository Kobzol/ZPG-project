#include "hud_module.h"

void HUDModule::startDraw(RenderComponent* component)
{
	Program& program = ProgramManager::getInstance().getCurrentProgram();
	program.setViewMatrix(glm::mat4());
}
void HUDModule::endDraw(RenderComponent* component)
{
	Program& program = ProgramManager::getInstance().getCurrentProgram();
	program.setViewMatrix(Game::getInstance().getCamera()->calculateViewMatrix());
}