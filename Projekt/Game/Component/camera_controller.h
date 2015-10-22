#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "camera.h"
#include "icomponent.h"
#include "../game.h"
#include "../Object/game_object.h"
#include "../Input/input_controller.h"
#include "../../Math/math_helper.h"

class CameraController : public IComponent
{
public:
	CameraController(float cameraSpeed = 1.0f, float mouseSensitivity = 1.0f);

	void update() override;

	float getPitch();
	float getYaw();

private:
	void setLookVector(Camera* camera, glm::vec3 vector);
	void handleMouseLook(Camera* camera);
	void handleMouseMove(Camera* camera);

	float cameraSpeed;
	float mouseSensitivity;

	bool lookVectorSet;

	float pitch;
	float yaw;
};