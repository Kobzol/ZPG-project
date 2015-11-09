#pragma once

#include "../Component/icomponent.h"
#include "../Object/game_object.h"
#include "../Physics/transform.h"
#include "../../Model/model.h"

class ModelRenderComponent : public IComponent
{
public:
	ModelRenderComponent(Model* model, glm::vec3 color = glm::vec3(1.0f));

	void update() override;

private:
	Model* model;
	glm::vec3 color;
};