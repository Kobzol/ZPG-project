#include "physics_handler.h"

void PhysicsHandler::simulate(const std::vector<GameObject*>& objects, size_t objectCount, float delta)
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

			this->checkForCollisions(objects, objectCount, physics);
		}
	}
}

void PhysicsHandler::checkForCollisions(const std::vector<GameObject*>& objects, size_t objectCount, IPhysicsComponent* physics)
{
	SphereBoundingBox* box = physics->getBoundingBox();

	if (box == nullptr) return;

	for (size_t i = 0; i < objectCount; i++)
	{
		IPhysicsComponent* remotePhysics = objects[i]->getPhysicsComponent();
		if (remotePhysics == nullptr || remotePhysics == physics) continue;

		SphereBoundingBox* remoteBox = remotePhysics->getBoundingBox();
		if (remoteBox == nullptr) continue;

		if (box->collidesWith(physics->getGameObject()->getTransform(), objects[i]->getTransform(), remoteBox))
		{
			physics->onCollision(objects[i]);
		}
	}
}