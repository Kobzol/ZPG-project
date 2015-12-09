#pragma once

#include <iostream>
#include <functional>

#include "iphysics_component.h"
#include "BoundingBox/sphere_bounding_box.h"

class BasicPhysicsComponent : public IPhysicsComponent
{
public:
	BasicPhysicsComponent(bool movable = false, SphereBoundingBox* box = nullptr);
	BasicPhysicsComponent(bool movable, SphereBoundingBox* box, std::function<void(IPhysicsComponent*, GameObject*)> callback);

	virtual bool isMovable() const override;
	virtual void onCollision(GameObject* object);
	virtual void update() override { };

private:
	bool movable;
	std::function<void(IPhysicsComponent*, GameObject*)> callback = nullptr;
};