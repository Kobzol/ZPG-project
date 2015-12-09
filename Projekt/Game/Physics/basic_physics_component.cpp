#include "basic_physics_component.h"

BasicPhysicsComponent::BasicPhysicsComponent(bool movable, SphereBoundingBox* box) : movable(movable), IPhysicsComponent(box)
{

}
BasicPhysicsComponent::BasicPhysicsComponent(bool movable, SphereBoundingBox* box, std::function<void(IPhysicsComponent*, GameObject*)> callback) : BasicPhysicsComponent(movable, box)
{
	this->callback = callback;
}

bool BasicPhysicsComponent::isMovable() const
{
	return this->movable;
}
void BasicPhysicsComponent::onCollision(GameObject* object)
{
	if (this->callback != nullptr)
	{
		this->callback(this, object);
	}
}