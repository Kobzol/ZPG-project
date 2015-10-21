#pragma once

#include <vector>

#include "iphysics_component.h"
#include "force.h"
#include "../Object/game_object.h"

class PhysicsHandler
{
public:
	void simulate(std::vector<GameObject*> objects, size_t objectCount, float delta);
};