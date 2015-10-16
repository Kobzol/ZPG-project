#pragma once

#include "../Component/icomponent.h"
#include "../Physics/transform.h"
#include "../tag.h"
#include "../../Helper/flags.h"

class GameObject
{
public:
	GameObject(IComponent* component);

	Transform& getTransform();
	IComponent* getScriptComponent();
	Flags<Tag>& getTags();

	int getId();
	void setId(int id);

	void update();
	void dispose();

private:
	GameObject(const GameObject& other);
	GameObject& operator=(const GameObject& other);

	int id;

	Transform transform;
	IComponent* scriptComponent;
	Flags<Tag> tags;
};