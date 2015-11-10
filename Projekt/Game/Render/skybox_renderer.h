#pragma once

#include "../Component/icomponent.h"
#include "../../Content/program_manager.h"
#include "../Object/game_object.h"
#include "../../Buffer/vao.h"
#include "../../Buffer/vbo.h"
#include "../../Model/cubemap.h"
#include "../../Model/vertex.h"
#include "../../Render/render_utils.h"
#include "../game.h"

class SkyboxRenderer : public IComponent
{
public:
	SkyboxRenderer(Cubemap cubemap);

	void update() override;
	void dispose() override;

private:
	VAO vao;
	VBO vbo;

	Cubemap cubemap;
};