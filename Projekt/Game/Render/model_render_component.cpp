#include "model_render_component.h"

ModelRenderComponent::ModelRenderComponent(Model* model, glm::vec3 color) : model(model), color(color)
{

}

void ModelRenderComponent::update()
{
	Program& program = ProgramManager::getInstance().use(ProgramManager::PROGRAM_MODEL);

	Transform& transform = this->gameObject->getTransform();

	program.setModelMatrix(this->gameObject->getTransform().getModel());
	program.setUniform3f("color", this->color);

	/*if (transform.isDirty())
	{
		
		transform.clearDirty({ TransformDirtyBit::Position, TransformDirtyBit::Rotation, TransformDirtyBit::Scale });
	}*/

	this->model->draw();
}