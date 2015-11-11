#pragma once

#include "irender_module.h"
#include "../../../Model/geometry_object.h"
#include "../../../Render/render_utils.h"

class GeometryDrawModule : public IRenderModule
{
public:
	GeometryDrawModule(GeometryObject geometry);

	void update(RenderComponent* component) override;
	void dispose() override;

private:
	GeometryObject geometry;
};