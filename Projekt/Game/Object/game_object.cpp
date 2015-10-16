#include "game_object.h"

GameObject::GameObject(IComponent* scriptComponent) : scriptComponent(scriptComponent), id(-1)
{
	scriptComponent->setGameObject(this);
}

Transform& GameObject::getTransform()
{
	return this->transform;
}
IComponent* GameObject::getScriptComponent()
{
	return this->scriptComponent;
}
Flags<Tag>& GameObject::getTags()
{
	return this->tags;
}

int GameObject::getId()
{
	return this->id;
}
void GameObject::setId(int id)
{
	this->id = id;
}

void GameObject::update()
{
	if (this->scriptComponent != nullptr)
	{
		this->scriptComponent->update();
	}
}

void GameObject::dispose()
{
	this->scriptComponent->dispose();
	delete this->scriptComponent;
}