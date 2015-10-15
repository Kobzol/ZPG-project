#pragma once

#include <glm/glm.hpp>

#include "iscript_component.h"
#include "../camera.h"
#include "../game.h"
#include "../game_object.h"
#include "../Input/input_controller.h"

class CameraController : public IScriptComponent
{
public:
	CameraController(float cameraSpeed = 1.0f, float mouseSensitivity = 0.05f);

	void update(GameObject* object) override;

private:
	void setLookVector(glm::vec3 vector);
	void handleMouseLook(Camera* camera);
	void handleMouseMove(Camera* camera);

	float cameraSpeed;
	float mouseSensitivity;

	bool lookVectorSet;

	float pitch;
	float yaw;
};