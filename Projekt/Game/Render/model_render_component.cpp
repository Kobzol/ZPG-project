#include "model_render_component.h"

ModelRenderComponent::ModelRenderComponent(Model* model) : model(model)
{

}

void ModelRenderComponent::update()
{
	Program& program = ProgramManager::getInstance().use(ProgramManager::PROGRAM_MODEL);

	Transform& transform = this->gameObject->getTransform();

	program.setModelMatrix(this->gameObject->getTransform().getModel());

	/*if (transform.isDirty())
	{
		
		transform.clearDirty({ TransformDirtyBit::Position, TransformDirtyBit::Rotation, TransformDirtyBit::Scale });
	}*/

	this->model->draw();
}