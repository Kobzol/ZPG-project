#pragma once

#include "../Component/icomponent.h"
#include "../Physics/iphysics_component.h"
#include "../Physics/transform.h"
#include "../tag.h"
#include "../../Helper/flags.h"

class GameObject
{
public:
	GameObject(IComponent* component=nullptr, IComponent* renderComponent=nullptr, IPhysicsComponent* physicsComponent=nullptr);

	Transform& getTransform();
	
	IComponent* getScriptComponent();
	IComponent* getRenderComponent();
	IPhysicsComponent* getPhysicsComponent();

	Flags<Tag>& getTags();

	int getId();
	void setId(int id);

	void update();
	void draw();
	void dispose();

private:
	GameObject(const GameObject& other);
	GameObject& operator=(const GameObject& other);

	int id;

	Transform transform;

	IComponent* scriptComponent;
	IComponent* renderComponent;
	IPhysicsComponent* physicsComponent;

	Flags<Tag> tags;
};