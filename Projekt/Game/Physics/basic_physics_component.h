#pragma once

#include "iphysics_component.h"

class BasicPhysicsComponent : public IPhysicsComponent
{
public:
	BasicPhysicsComponent(bool movable = false, bool collidable = false);

	virtual bool isMovable() const override;
	virtual bool isCollidable() const override;
	virtual void onCollision(GameObject* object) { };

	virtual void update() override { };

private:
	bool movable;
	bool collidable;
};