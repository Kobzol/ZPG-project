#include "game_object.h"

GameObject::GameObject(std::string name, IComponent* scriptComponent, IComponent* renderComponent, IPhysicsComponent* physicsComponent)
	: name(name), scriptComponent(scriptComponent), renderComponent(renderComponent), physicsComponent(physicsComponent), id(-1)
{
	if (scriptComponent != nullptr)
	{
		scriptComponent->setGameObject(this);
	}

	if (renderComponent != nullptr)
	{
		renderComponent->setGameObject(this);
	}

	if (physicsComponent != nullptr)
	{
		physicsComponent->setGameObject(this);
	}
}
GameObject::GameObject(IComponent* scriptComponent, IComponent* renderComponent, IPhysicsComponent* physicsComponent)
	: scriptComponent(scriptComponent), renderComponent(renderComponent), physicsComponent(physicsComponent), id(-1)
{
	if (scriptComponent != nullptr)
	{
		scriptComponent->setGameObject(this);
	}
	
	if (renderComponent != nullptr)
	{
		renderComponent->setGameObject(this);
	}

	if (physicsComponent != nullptr)
	{
		physicsComponent->setGameObject(this);
	}
}

Transform& GameObject::getTransform()
{
	return this->transform;
}
IComponent* GameObject::getScriptComponent()
{
	return this->scriptComponent;
}
IComponent* GameObject::getRenderComponent()
{
	return this->renderComponent;
}
IPhysicsComponent* GameObject::getPhysicsComponent()
{
	return this->physicsComponent;
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

std::string GameObject::getName()
{
	return this->name;
}
void GameObject::setName(const std::string& name)
{
	this->name = name;
}

void GameObject::update()
{
	if (this->scriptComponent != nullptr)
	{
		this->scriptComponent->update();
	}
}
void GameObject::draw()
{
	if (this->renderComponent != nullptr)
	{
		this->renderComponent->update();
	}
}

void GameObject::dispose()
{
	if (this->scriptComponent != nullptr)
	{
		this->scriptComponent->dispose();
		delete this->scriptComponent;
	}
	
	if (this->renderComponent != nullptr)
	{
		this->renderComponent->dispose();
		delete this->renderComponent;
	}
}