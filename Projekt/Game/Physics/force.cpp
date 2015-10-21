#include "force.h"

Force::Force(glm::vec3 direction, float strength) : direction(direction), strength(strength)
{

}

glm::vec3 Force::getDirection()
{
	return this->direction;
}
float Force::getStrength()
{
	return this->strength;
}

void Force::applyTo(Transform& transform, float delta)
{
	transform.moveBy(this->direction * this->strength * delta);
}