#pragma once

#include "force.h"
#include "BoundingBox/sphere_bounding_box.h"
#include "../Component/icomponent.h"

class GameObject;

class IPhysicsComponent : public IComponent
{
public:
	IPhysicsComponent() : box(nullptr) { }
	IPhysicsComponent(SphereBoundingBox* box) : box(box) { }

	virtual bool isMovable() const  = 0;
	virtual SphereBoundingBox* getBoundingBox() { return this->box; }
	virtual void onCollision(GameObject* object) = 0;
	Force& getForce() { return this->force; }

	virtual void dispose()
	{
		delete this->box;
	}

protected:
	Force force;
	SphereBoundingBox* box;
};