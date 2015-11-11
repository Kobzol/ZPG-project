#pragma once

#include "irender_module.h"
#include "../../game.h"
#include "../../../Content/program_manager.h"
#include "../../../Content/texture_manager.h"
#include "../../../Context/context.h"
#include "../../../Model/geometry_object.h"
#include "../../../Model/texture.h"
#include "../../../Render/render_utils.h"

class SpriteDrawModule : public IRenderModule
{
public:
	SpriteDrawModule(std::string textureId);

	void update(RenderComponent* component) override;
	void dispose() override;

private:
	GeometryObject spriteGeometry;

	std::string textureId;
};