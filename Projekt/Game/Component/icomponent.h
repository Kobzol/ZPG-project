#pragma once

class GameObject;

class IComponent
{
public:
	virtual void update() = 0;

	virtual void dispose() { };

	virtual void setGameObject(GameObject* gameObject)
	{
		this->gameObject = gameObject;
	}
	GameObject* getGameObject()
	{
		return this->gameObject;
	}

protected:
	GameObject* gameObject;
};