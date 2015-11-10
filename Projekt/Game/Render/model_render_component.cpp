#include "model_render_component.h"
#include "../game.h"

ModelRenderComponent::ModelRenderComponent(Model* model, glm::vec3 color) : model(model), color(color)
{

}

void ModelRenderComponent::update()
{
	Program& program = ProgramManager::getInstance().use(ProgramManager::PROGRAM_MODEL);
	Context& context = Game::getInstance().getContext();

	Transform& transform = this->gameObject->getTransform();

	program.setModelMatrix(this->gameObject->getTransform().getModel());
	program.setUniform3f("color", this->color);

	/*if (transform.isDirty())
	{
		
		transform.clearDirty({ TransformDirtyBit::Position, TransformDirtyBit::Rotation, TransformDirtyBit::Scale });
	}*/

	context.setStencilFunc(GL_ALWAYS, this->getGameObject()->getId(), 0xFF);
	this->model->draw();
}