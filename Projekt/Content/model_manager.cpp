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
const std::string ModelManager::MODEL_MGA_PODLAHA = "mga/podlaha";
const std::string ModelManager::MODEL_MGA_MEC = "mga/mec";
const std::string ModelManager::MODEL_MGA_KYTARA = "mga/kytara";

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
	this->load("mga/projekt/wall", new Model(MODEL_PATH + "mga/projekt/wall/wall.obj"));
	this->load("mga/projekt/battlements", new Model(MODEL_PATH + "mga/projekt/battlements/battlements.obj"));
	this->load("mga/projekt/gate", new Model(MODEL_PATH + "mga/projekt/gate/gate.obj"));
	this->load("mga/projekt/grass", new Model(MODEL_PATH + "mga/projekt/grass/grass.obj"));
	this->load("mga/projekt/chair", new Model(MODEL_PATH + "mga/projekt/chair/chair.obj"));
	this->load("mga/projekt/gallows", new Model(MODEL_PATH + "mga/projekt/gallows/gallows.obj"));
	this->load("mga/projekt/rope", new Model(MODEL_PATH + "mga/projekt/rope/rope.obj"));
	this->load("mga/projekt/skeleton", new Model(MODEL_PATH + "mga/projekt/skeleton/skeleton.obj"));
	this->load("mga/projekt/sword", new Model(MODEL_PATH + "mga/projekt/sword/sword.obj"));
	this->load("mga/projekt/catapult", new Model(MODEL_PATH + "mga/projekt/catapult/catapult.obj"));
	this->load("mga/projekt/weapons", new Model(MODEL_PATH + "mga/projekt/weapons/weapons.obj"));
	this->load("mga/projekt/tower", new Model(MODEL_PATH + "mga/projekt/tower/tower.obj"));
	this->load("mga/projekt/bench", new Model(MODEL_PATH + "mga/projekt/bench/bench.obj"));
	this->load("mga/projekt/coins", new Model(MODEL_PATH + "mga/projekt/coins/coins.obj"));
	this->load("mga/projekt/crate", new Model(MODEL_PATH + "mga/projekt/crate/crate.obj"));

	//this->load(ModelManager::MODEL_HOUSE, new Model(MODEL_PATH + "house/test.obj"));
	//this->load(ModelManager::MODEL_TREE, new Model(MODEL_PATH + "ber0134/80_final.obj"));
	//this->load(ModelManager::MODEL_M4, new Model(MODEL_PATH + "M4/m4a1_s.fbx"));
	//this->load(ModelManager::MODEL_TIE, new Model(MODEL_PATH + "tie/tie.obj"));
	//this->load(ModelManager::MODEL_XWING, new Model(MODEL_PATH + "xwing/star-wars-x-wing.obj"));
	//this->load(ModelManager::MODEL_BLASTER, new Model(MODEL_PATH + "blaster/Blaster DC-15s.obj"));
	//this->load(ModelManager::MODEL_GROUND, new Model(MODEL_PATH + "ground/ground.obj"));
	//this->load(ModelManager::MODEL_AT_AT, new Model(MODEL_PATH + "at_at/at_at.obj"));
	//this->load(ModelManager::MODEL_DEATHSTAR, new Model(MODEL_PATH + "deathstar/ds.obj"));
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