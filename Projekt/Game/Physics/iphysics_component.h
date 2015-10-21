#pragma once

#include "force.h"
#include "../Component/icomponent.h"

class GameObject;

class IPhysicsComponent : public IComponent
{
public:
	virtual bool isMovable() const  = 0;
	virtual bool isCollidable() const = 0;
	virtual void onCollision(GameObject* object) = 0;
	Force& getForce() { return this->force; }

protected:
	Force force;
};