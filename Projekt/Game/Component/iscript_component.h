#pragma once

class GameObject;

class IScriptComponent
{
public:
	virtual void update(GameObject* gameObject) = 0;
};