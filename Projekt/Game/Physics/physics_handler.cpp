#include "physics_handler.h"

void PhysicsHandler::simulate(std::vector<GameObject*> objects, size_t objectCount, float delta)
{
	for (size_t i = 0; i < objectCount; i++)
	{
		GameObject* obj = objects[i];
		IPhysicsComponent* physics = obj->getPhysicsComponent();
		
		if (physics != nullptr)
		{
			if (physics->isMovable())
			{
				Force& force = physics->getForce();
				force.applyTo(obj->getTransform(), delta);
			}
		}
	}
}