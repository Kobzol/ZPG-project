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

	GameObject* bullet = new GameObject(nullptr, RenderUtils::createCubeRenderer(Color::Yellow), new BasicPhysicsComponent(true, new SphereBoundingBox(1.0f)));
	bullet->getTransform().setPosition(playerPosition->getTransform().getPosition());
	bullet->getTransform().setScale(glm::vec3(0.5f));
	bullet->getPhysicsComponent()->getForce().setDirection(camera->getFront());
	bullet->getPhysicsComponent()->getForce().setStrength(1.0f);

	Game::getInstance().getActiveScene().add(bullet);
}