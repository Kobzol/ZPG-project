#pragma once

#include "Component/iscript_component.h"
#include "Physics/itransformable.h"
#include "Physics/transform.h"
#include "tag.h"
#include "../Helper/flags.h"

class GameObject : public ITransformable
{
public:
	GameObject(IScriptComponent* component);

	Transform& getTransform();
	Flags<Tag>& getTags();

	void update();
	void dispose();

	virtual glm::mat4 getModel() const;

	virtual glm::vec3 getPosition() const;
	virtual glm::quat getRotation() const;
	virtual glm::vec3 getScale() const;

	virtual void setPosition(const glm::vec3 &position);
	virtual void moveBy(const glm::vec3 &offset);

	virtual void setRotation(float angle, const glm::vec3 &axis);
	virtual void rotateBy(float angle, const glm::vec3 &axis);

	virtual void setScale(const glm::vec3 &scale);
	virtual void scaleBy(const glm::vec3 &scale);

	virtual void reset();

private:
	GameObject(const GameObject& other);
	GameObject& operator=(const GameObject& other);

	Flags<Tag> tags;
	Transform transform;
	IScriptComponent* scriptComponent;
};