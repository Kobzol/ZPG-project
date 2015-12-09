#pragma once

#include "irender_module.h"
#include "../../game.h"
#include "../../../Context/context.h"
#include "../../../Model/cubemap.h"
#include "../../../Model/geometry_object.h"
#include "../../../Render/render_utils.h"

class SkyboxDrawModule : public IRenderModule
{
public:
	SkyboxDrawModule(Cubemap cubemap);

	void startDraw(RenderComponent* component) override;
	void dispose() override;

private:
	GeometryObject geometry;
	Cubemap cubemap;
};