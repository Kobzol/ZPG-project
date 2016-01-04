#include "weapon_controller.h"

void WeaponController::update()
{
	this->clickTimer.update(Game::getInstance().getDeltaTime());

	if (this->clickTimer.isReady() && InputController::getInstance().isLeftMouseDown())
	{
		this->shoot();
		this->clickTimer.reset();
	}
}

void WeaponController::shoot()
{
	AudioManager::getInstance().play2DForget(AudioManager::AUDIO_GUNSHOT);
	Game& game = Game::getInstance();

	Camera* camera = game.getCamera();
	GameObject* playerPosition = camera->getGameObject();

	GameObject* bullet = new GameObject(nullptr, RenderUtils::createCubeRenderer(Color::Red), new BasicPhysicsComponent(true, new SphereBoundingBox(1.0f),
	[](IPhysicsComponent* component, GameObject* object)
	{
		if (object->getTags().isSet(Tag::Target))
		{
			Game::getInstance().getActiveScene().getObjectManager().markForRemoval(object);
			Game::getInstance().getActiveScene().getObjectManager().markForRemoval(component->getGameObject());

			std::cout << "Hit box!" << std::endl;
		}
	}));
	bullet->getTransform().setPosition(playerPosition->getTransform().getPosition());
	bullet->getTransform().setScale(glm::vec3(0.2f));
	bullet->getPhysicsComponent()->getForce().setDirection(camera->getFront());
	bullet->getPhysicsComponent()->getForce().setStrength(0.1f);
	bullet->getTags().set(Tag::Bullet);

	Game::getInstance().getActiveScene().add(bullet);
}