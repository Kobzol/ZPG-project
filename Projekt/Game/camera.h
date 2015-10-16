#pragma once

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Component/iscript_component.h"
#include "Content/program_manager.h"
#include "Object/game_object.h"
#include "Physics/transform.h"
#include "../Event/camera_changed_listener.h"
#include "../Event/event_broadcaster.h"

class Camera : public IScriptComponent
{
public:
	Camera(
		IScriptComponent* controller,
		glm::vec3 target = glm::vec3(0.0f),
		float fov = 45.0f,
		float aspect = 4.0f / 3.0f,
		float nearPlane = 1.0f,
		float farPlane = 10.0f
	);

	void update() override;
	void setGameObject(GameObject* object) override;

	void setTarget(glm::vec3 target);

	glm::vec3 getLeft();
	glm::vec3 getUp();
	glm::vec3 getFront();

	void setFov(float fov);
	void setAspect(float aspect);
	void setNearPlane(float nearPlane);
	void setFarPlane(float farPlane);

	glm::mat4 calculateViewMatrix();
	glm::mat4 calculateProjectionMatrix();

	void dispose() override;

private:
	Camera(const Camera& other);
	Camera& operator=(const Camera& other);

	glm::vec3 target;

	float fov;
	float aspect;
	float nearPlane;
	float farPlane;

	IScriptComponent* controller;
	bool perspectiveDirty;
};