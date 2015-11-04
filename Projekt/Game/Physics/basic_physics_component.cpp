#include "basic_physics_component.h"

BasicPhysicsComponent::BasicPhysicsComponent(bool movable, SphereBoundingBox* box) : movable(movable), IPhysicsComponent(box)
{

}
bool BasicPhysicsComponent::isMovable() const 
{
	return this->movable;
}