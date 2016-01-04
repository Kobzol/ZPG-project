#include "model_manager.h"

const std::string ModelManager::MODEL_CUBE = "cube";
const std::string ModelManager::MODEL_NANOSUIT = "nanosuit";
const std::string ModelManager::MODEL_M4 = "m4";
const std::string ModelManager::MODEL_TREE = "tree";
const std::string ModelManager::MODEL_HOUSE = "house";
const std::string ModelManager::MODEL_TIE = "tie";
const std::string ModelManager::MODEL_XWING = "xwing";
const std::string ModelManager::MODEL_BLASTER = "blaster";
const std::string ModelManager::MODEL_GROUND = "ground";
const std::string ModelManager::MODEL_AT_AT = "at_at";
const std::string ModelManager::MODEL_DEATHSTAR = "deathstar";

const std::string ModelManager::MODEL_PATH = "Resources/Models/";

ModelManager ModelManager::instance = ModelManager();

ModelManager& ModelManager::getInstance()
{
	return ModelManager::instance;
}

ModelManager::ModelManager()
{

}

void ModelManager::preloadModels()
{
	this->load(ModelManager::MODEL_CUBE, new Model(MODEL_PATH + "cube_normal_map/texture_normal_cube.obj"));
	this->load(ModelManager::MODEL_HOUSE, new Model(MODEL_PATH + "house/test.obj"));
	//this->load(ModelManager::MODEL_TREE, new Model(MODEL_PATH + "ber0134/80_final.obj"));
	//this->load(ModelManager::MODEL_M4, new Model(MODEL_PATH + "M4/m4a1_s.fbx"));
	this->load(ModelManager::MODEL_TIE, new Model(MODEL_PATH + "tie/tie.obj"));
	this->load(ModelManager::MODEL_XWING, new Model(MODEL_PATH + "xwing/star-wars-x-wing.obj"));
	this->load(ModelManager::MODEL_BLASTER, new Model(MODEL_PATH + "blaster/Blaster DC-15s.obj"));
	this->load(ModelManager::MODEL_GROUND, new Model(MODEL_PATH + "ground/ground.obj"));
	this->load(ModelManager::MODEL_AT_AT, new Model(MODEL_PATH + "at_at/at_at.obj"));
	this->load(ModelManager::MODEL_DEATHSTAR, new Model(MODEL_PATH + "deathstar/ds.obj"));
	//this->load(ModelManager::MODEL_NANOSUIT, new Model(MODEL_PATH + "nanosuit/nanosuit.obj"));
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