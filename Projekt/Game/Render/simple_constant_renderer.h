#pragma once

#include "../Component/icomponent.h"
#include "../../Content/program_manager.h"
#include "../Object/game_object.h"
#include "../../Buffer/vao.h"
#include "../../Buffer/vbo.h"
#include "../../Model/geometry_object.h"
#include "../../Model/vertex.h"
#include "../../Render/render_utils.h"
#include "../game.h"

class SimpleConstantRenderer : public IComponent
{
public:
	SimpleConstantRenderer(GeometryObject geometryObject, std::string shader, glm::vec3 color = glm::vec3(1.0f));

	void update() override;
	void dispose() override;

private:
	GeometryObject geometryObject;
	std::string shader;
	glm::vec3 color;
};