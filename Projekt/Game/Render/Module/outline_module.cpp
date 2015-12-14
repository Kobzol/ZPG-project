#include "outline_module.h"
#include "../../game.h"
#include "../../../Content/program_manager.h"
#include "../../../Context/context.h"

OutlineModule::OutlineModule(IRenderModule* module) : module(module)
{

}

void OutlineModule::startDraw(RenderComponent* component)
{
	
	Context& context = Game::getInstance().getContext();

	if (Game::getInstance().getRenderPass() == RenderPass::Render)
	{
		context.setStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
		context.setStencilFunc(GL_ALWAYS, 1, 0xFF);	// passes stencil test always
		context.setStencilMask(0xFF);	// enable writing to stencil buffer

		this->module->draw(component);

		context.setStencilFunc(GL_NOTEQUAL, 1, 0xFF);	// passes stencil test if value is not equal to 1
		context.setStencilMask(0x00);	// disable writing to stencil buffer
		context.setDepthTest(false);

		glm::vec3 scale = component->getGameObject()->getTransform().getScale();
		component->getGameObject()->getTransform().setScale(scale * 1.1f);

		std::string programName = ProgramManager::getInstance().getCurrentProgramName();

		Program& program = ProgramManager::getInstance().use(ProgramManager::PROGRAM_GEOMETRY_CONSTANT);
		program.setUniform3f("color", Color::Red);
		program.setModelMatrix(component->getGameObject()->getTransform().getModel());

		this->module->draw(component);

		component->getGameObject()->getTransform().setScale(scale);
		ProgramManager::getInstance().use(programName);

		context.setDepthTest(true);
		context.setStencilMask(0xFF);
		context.setStencilFunc(GL_ALWAYS, 1, 0xFF);
		context.setStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	}
}