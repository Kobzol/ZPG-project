#pragma once

#include <glm/glm.hpp>

#include <string>
#include <vector>

#include "Module/irender_module.h"
#include "../game.h"
#include "../Component/icomponent.h"
#include "../../Content/program_manager.h"
#include "../../Context/context.h"
#include "../../Render/program.h"

class RenderComponent : public IComponent
{
public:
	RenderComponent(glm::vec3 color, std::string shader, IRenderModule* module);
	RenderComponent(glm::vec3 color, std::string shader, const std::vector<IRenderModule*>& modules);

	void update() override;
	void dispose() override;

private:
	glm::vec3 color;
	std::string shader;
	std::vector<IRenderModule*> modules;
};