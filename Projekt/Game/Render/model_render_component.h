#pragma once

#include "../Component/icomponent.h"
#include "../Object/game_object.h"
#include "../Physics/transform.h"
#include "../../Model/model.h"

class ModelRenderComponent : public IComponent
{
public:
	ModelRenderComponent(Model* model);

	void update() override;

private:
	Model* model;
};