#pragma once

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "game_object.h"
#include "../Event/camera_changed_listener.h"
#include "../Event/event_broadcaster.h"

class Camera : public GameObject
{
public:
	Camera(
		IScriptComponent* component,
		glm::vec3 position = glm::vec3(0.0f),
		glm::vec3 target = glm::vec3(0.0f),
		float fov = 45.0f,
		float aspect = 4.0f / 3.0f,
		float nearPlane = 1.0f,
		float farPlane = 10.0f
	);

	void setPosition(const glm::vec3& position) override;
	void moveBy(const glm::vec3& offset) override;
	void setRotation(float angle, const glm::vec3& axis) override;
	void rotateBy(float angle, const glm::vec3& axis) override;
	void setTarget(glm::vec3 target);

	glm::vec3 getLeft();
	glm::vec3 getUp();
	glm::vec3 getFront();

	void setFov(float fov);
	void setAspect(float aspect);
	void setNearPlane(float nearPlane);
	void setFarPlane(float farPlane);

	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix();

	void attachListener(CameraChangedListener* listener);
	void detachListener(CameraChangedListener* listener);

private:
	Camera(const Camera& other);
	Camera& operator=(const Camera& other);

	void recalculateViewMatrix();
	void recalculateProjectionMatrix();

	glm::vec3 target;

	float fov;
	float aspect;
	float nearPlane;
	float farPlane;

	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;

	EventBroadcaster broadcaster;
};