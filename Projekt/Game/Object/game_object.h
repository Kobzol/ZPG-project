#pragma once

#include "../Component/iscript_component.h"
#include "../Physics/transform.h"
#include "../tag.h"
#include "../../Helper/flags.h"

class GameObject
{
public:
	GameObject(IScriptComponent* component);

	Transform& getTransform();
	IScriptComponent* getScriptComponent();
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
	IScriptComponent* scriptComponent;
	Flags<Tag> tags;
};