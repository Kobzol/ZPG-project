#include "basic_physics_component.h"

BasicPhysicsComponent::BasicPhysicsComponent(bool movable, bool collidable) : movable(movable), collidable(collidable)
{

}

bool BasicPhysicsComponent::isMovable() const 
{
	return this->movable;
}
bool BasicPhysicsComponent::isCollidable() const
{
	return this->collidable;
}