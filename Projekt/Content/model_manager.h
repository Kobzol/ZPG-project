#pragma once

#include "content_manager.h"
#include "../../Model/model.h"

class ModelManager : public ContentManager<Model*>
{
public:
	static const std::string MODEL_CUBE;

	static ModelManager& getInstance();

	void preloadModels();

	void dispose();

private:
	static const std::string MODEL_PATH;

	static ModelManager instance;

	ModelManager();
};