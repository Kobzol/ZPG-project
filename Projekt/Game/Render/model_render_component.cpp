#include "model_render_component.h"

ModelRenderComponent::ModelRenderComponent(Model* model) : model(model)
{

}

void ModelRenderComponent::update()
{
	Transform& transform = this->gameObject->getTransform();

	if (transform.isDirty())
	{
		ProgramManager::getInstance().getCurrentProgram().setModelMatrix(this->gameObject->getTransform().getModel());
		transform.clearDirty({ TransformDirtyBit::Position, TransformDirtyBit::Rotation, TransformDirtyBit::Scale });
	}

	this->model->draw();
}