#pragma once

#include "force.h"
#include "../Component/icomponent.h"

class GameObject;

class IPhysicsComponent : public IComponent
{
public:
	virtual bool isMovable() { return false; }
	virtual bool isCollidable() { return false; }
	virtual bool onCollision(GameObject* object) { }
	virtual Force& getForce() { return this->force; }

protected:
	Force force;
};