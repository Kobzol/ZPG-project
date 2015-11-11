#include "model_draw_module.h"

ModelDrawModule::ModelDrawModule(std::string modelName) : modelName(modelName)
{

}

void ModelDrawModule::update(RenderComponent* component)
{
	ModelManager::getInstance().get(this->modelName)->draw();
}