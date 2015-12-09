#pragma once

#include "irender_module.h"
#include "../../game.h"

class HUDModule : public IRenderModule
{
public:
	HUDModule(glm::vec3 position = glm::vec3(0.0f));

	virtual void startDraw(RenderComponent* component);
	virtual void endDraw(RenderComponent* component);

private:
	glm::vec3 position;
};