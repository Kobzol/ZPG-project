#pragma once

#include <iostream>

#include "iphysics_component.h"
#include "BoundingBox/sphere_bounding_box.h"

class BasicPhysicsComponent : public IPhysicsComponent
{
public:
	BasicPhysicsComponent(bool movable = false, SphereBoundingBox* box = nullptr);

	virtual bool isMovable() const override;
	virtual void onCollision(GameObject* object) { }
	virtual void update() override { };

private:
	bool movable;
};