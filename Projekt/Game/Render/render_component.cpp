#include "render_component.h"

RenderComponent::RenderComponent(glm::vec3 color, std::string shader, IRenderModule* module) : color(color), shader(shader), module(module)
{
	
}

void RenderComponent::update()
{
	Program& program = ProgramManager::getInstance().use(this->shader);
	Context& context = Game::getInstance().getContext();

	program.setModelMatrix(this->gameObject->getTransform().getModel());
	program.setUniform3f("color", this->color);

	context.setStencilFunc(GL_ALWAYS, this->getGameObject()->getId(), 0xFF);

	module->draw(this);
}

glm::vec3 RenderComponent::getColor() const
{
	return this->color;
}

void RenderComponent::dispose()
{
	this->module->dispose();
	delete this->module;
}