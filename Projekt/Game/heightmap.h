#pragma once

#include <memory>

#include "Object/game_object.h"
#include "Render/render_component.h"
#include "../Model/geometry_object.h"

class HeightMap
{
public:
	HeightMap(size_t size = 256, float granularity = 0.01f, float textureScale = 4.0f);

	GameObject* createObject();

private:
	std::unique_ptr<GeometryObject> geometryObject;
};