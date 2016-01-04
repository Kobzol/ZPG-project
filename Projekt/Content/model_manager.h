#pragma once

#include "content_manager.h"
#include "../../Model/model.h"

class ModelManager : public ContentManager<Model*>
{
public:
	static const std::string MODEL_CUBE;
	static const std::string MODEL_NANOSUIT;
	static const std::string MODEL_M4;
	static const std::string MODEL_TREE;
	static const std::string MODEL_HOUSE;
	static const std::string MODEL_TIE;
	static const std::string MODEL_XWING;
	static const std::string MODEL_BLASTER;
	static const std::string MODEL_GROUND;
	static const std::string MODEL_AT_AT;

	static ModelManager& getInstance();

	void preloadModels();

	void dispose();

private:
	static const std::string MODEL_PATH;

	static ModelManager instance;

	ModelManager();
};