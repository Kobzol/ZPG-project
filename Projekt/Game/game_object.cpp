#include "game_object.h"

GameObject::GameObject(IScriptComponent* scriptComponent) : scriptComponent(scriptComponent)
{

}

Transform& GameObject::getTransform()
{
	return this->transform;
}

void GameObject::update()
{
	if (this->scriptComponent != nullptr)
	{
		this->scriptComponent->update(this);
	}
}

void GameObject::dispose()
{
	delete this->scriptComponent;
}