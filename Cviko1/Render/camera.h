#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera
{
private:
	glm::vec3 position;
	glm::vec3 target;
	glm::vec3 up;

	float fov;
	float aspect;
	float nearPlane;
	float farPlane;

	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;

	void recalculateViewMatrix();
	void recalculateProjectionMatrix();

public:
	Camera(
		glm::vec3 position = glm::vec3(0.0f),
		glm::vec3 target = glm::vec3(0.0f),
		glm::vec3 up = glm::vec3(0.0f, 0.0f, 1.0f),
		float fov = 45.0f,
		float aspect = 800.0f / 600.0f,
		float nearPlane = 1.0f,
		float farPlane = 10.0f
	);

	void setPosition(glm::vec3 position);
	void setTarget(glm::vec3 target);
	void setUpVector(glm::vec3 up);

	void setFov(float fov);
	void setAspect(float aspect);
	void setNearPlane(float nearPlane);
	void setFarPlane(float farPlane);

	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix();
};