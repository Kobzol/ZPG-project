#pragma once

#include "Component/iscript_component.h"
#include "Physics/transform.h"

class GameObject
{
public:
	GameObject(IScriptComponent* component);

	Transform& getTransform();

	void update();
	void dispose();

private:
	GameObject(const GameObject& other);
	GameObject& operator=(const GameObject& other);

	Transform transform;
	IScriptComponent* scriptComponent;
};