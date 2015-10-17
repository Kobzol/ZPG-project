#pragma once

#include "../Component/icomponent.h"
#include "../Content/program_manager.h"
#include "../Object/game_object.h"
#include "../../Buffer/vao.h"
#include "../../Buffer/vbo.h"
#include "../../Model/vertex.h"
#include "../../Render/render_utils.h"
#include "../game.h"

class VertexRenderComponent : public IComponent
{
public:
	VertexRenderComponent(const Vertex* data, size_t verticesCount);

	void update() override;
	void dispose() override;

private:
	VAO vao;
	VBO vbo;

	size_t verticesCount;
};