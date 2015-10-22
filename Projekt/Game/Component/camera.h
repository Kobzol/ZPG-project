#pragma once

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "icomponent.h"
#include "../Object/game_object.h"
#include "../Physics/transform.h"
#include "../../Content/program_manager.h"
#include "../../Helper/flags.h"

enum class CameraDirtyBit
{
	Target,
	Perspective
};

class Camera : public IComponent
{
public:
	Camera(
		IComponent* controller,
		glm::vec3 target = glm::vec3(0.0f),
		float fov = 45.0f,
		float aspect = 4.0f / 3.0f,
		float nearPlane = 1.0f,
		float farPlane = 10.0f
	);

	void update() override;
	void setGameObject(GameObject* object) override;

	IComponent* getController();

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

	bool isDirty(std::initializer_list<CameraDirtyBit> bits);
	void clearDirty(std::initializer_list<CameraDirtyBit> bits);
	void setDirty(std::initializer_list<CameraDirtyBit> bits);

	glm::vec3 target;

	float fov;
	float aspect;
	float nearPlane;
	float farPlane;

	IComponent* controller;

	Flags<CameraDirtyBit> dirty;

	std::string lastUsedProgram;
};