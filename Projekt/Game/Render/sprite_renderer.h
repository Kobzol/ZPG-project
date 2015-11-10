#pragma once

#include <string>

#include <glm/glm.hpp>

#include "../game.h"
#include "../Component/icomponent.h"
#include "../../Content/program_manager.h"
#include "../../Content/texture_manager.h"
#include "../../Context/context.h"
#include "../../Model/geometry_object.h"
#include "../../Model/vertex.h"
#include "../../Render/render_utils.h"

class SpriteRenderer : public IComponent
{
public:
	SpriteRenderer(std::string textureId, const glm::vec4& color = glm::vec4(1.0f));

	void update() override;

private:
	GeometryObject spriteGeometry;

	std::string textureId;
	glm::vec4 color;
};