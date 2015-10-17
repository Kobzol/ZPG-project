#include "model_manager.h"

ModelManager ModelManager::instance = ModelManager();
const std::string ModelManager::MODEL_PATH = "models/";

const std::string ModelManager::MODEL_CUBE = "cube";

ModelManager& ModelManager::getInstance()
{
	return ModelManager::instance;
}

ModelManager::ModelManager()
{

}

void ModelManager::preloadModels()
{
	this->load(ModelManager::MODEL_CUBE, new Model(MODEL_PATH + "cube/cube.obj"));
}

void ModelManager::dispose()
{
	for (auto model : this->items)
	{
		model.second->dispose();
		delete model.second;
	}

	this->items.clear();
}