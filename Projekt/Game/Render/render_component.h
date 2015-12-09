#pragma once

#include <glm/glm.hpp>

#include <string>
#include <vector>

#include "render_pass.h"
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

	void update() override;
	void dispose() override;

	glm::vec3 getColor() const;

private:
	glm::vec3 color;
	std::string shader;
	IRenderModule* module;
};