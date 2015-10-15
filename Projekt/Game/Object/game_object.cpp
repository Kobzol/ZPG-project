#include "game_object.h"

GameObject::GameObject(IScriptComponent* scriptComponent) : scriptComponent(scriptComponent), id(-1)
{

}

Transform& GameObject::getTransform()
{
	return this->transform;
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
		this->scriptComponent->update(this);
	}
}

void GameObject::dispose()
{
	delete this->scriptComponent;
}

glm::mat4 GameObject::getModel() const
{
	return this->transform.getModel();
}

glm::vec3 GameObject::getPosition() const
{
	return this->transform.getPosition();
}
glm::quat GameObject::getRotation() const
{
	return this->transform.getRotation();
}
glm::vec3 GameObject::getScale()  const
{
	return this->transform.getScale();
}

void GameObject::setPosition(const glm::vec3 &position)
{
	this->transform.setPosition(position);
}
void GameObject::moveBy(const glm::vec3 &offset)
{
	this->transform.moveBy(offset);
}

void GameObject::setRotation(float angle, const glm::vec3 &axis)
{
	this->transform.setRotation(angle, axis);
}
void GameObject::rotateBy(float angle, const glm::vec3 &axis)
{
	this->transform.rotateBy(angle, axis);
}

void GameObject::setScale(const glm::vec3 &scale)
{
	this->transform.setScale(scale);
}
void GameObject::scaleBy(const glm::vec3 &scale)
{
	this->transform.scaleBy(scale);
}

void GameObject::reset()
{
	this->transform.reset();
}