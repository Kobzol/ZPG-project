#pragma once

#include <vector>

#include "iphysics_component.h"
#include "force.h"
#include "../Object/game_object.h"

class PhysicsHandler
{
public:
	void simulate(const std::vector<GameObject*>& objects, size_t objectCount, float delta);

	void checkForCollisions(const std::vector<GameObject*>& objects, size_t objectCount, IPhysicsComponent* physics);
};