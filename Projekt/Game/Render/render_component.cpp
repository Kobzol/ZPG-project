#include "render_component.h"

RenderComponent::RenderComponent(glm::vec3 color, std::string shader, const std::vector<IRenderModule*>& modules) : color(color), shader(shader), modules(modules)
{

}

void RenderComponent::update()
{
	Program& program = ProgramManager::getInstance().use(this->shader);
	Context& context = Game::getInstance().getContext();

	program.setModelMatrix(this->gameObject->getTransform().getModel());
	program.setUniform3f("color", this->color);

	context.setStencilFunc(GL_ALWAYS, this->getGameObject()->getId(), 0xFF);

	for (IRenderModule* module : this->modules)
	{
		module->update(this);
	}
}
void RenderComponent::dispose()
{
	for (IRenderModule* module : this->modules)
	{
		module->dispose();
		delete module;
	}
}