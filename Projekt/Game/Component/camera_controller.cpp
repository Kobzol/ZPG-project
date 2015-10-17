#include "camera_controller.h"

CameraController::CameraController(float cameraSpeed, float mouseSensitivity) : cameraSpeed(cameraSpeed), mouseSensitivity(mouseSensitivity), lookVectorSet(false)
{

}

void CameraController::update()
{
	Camera* camera = (Camera*) this->gameObject->getScriptComponent();

	this->handleMouseMove(camera);

	if (!this->lookVectorSet)	// TODO: set front vector according to up vector
	{
		this->setLookVector(camera->getFront());
		this->lookVectorSet = true;
	}
	else
	{
		this->handleMouseLook(camera);
	}
}

void CameraController::setLookVector(glm::vec3 vector)
{
	vector = glm::normalize(vector);

	glm::vec3 zeroHorizontalVector = glm::normalize(glm::vec3(1.0f, 0.0f, 0.0f));
	glm::vec3 zeroVerticalVector = glm::normalize(glm::vec3(0.0f, 0.0f, -1.0f));

	float cos = glm::dot(vector, zeroHorizontalVector);
	this->yaw = -glm::degrees(acos(cos));

	cos = glm::dot(vector, zeroVerticalVector);
	this->pitch = glm::degrees(acos(cos));
}
void CameraController::handleMouseLook(Camera* camera)
{
	glm::vec2 mousePos = InputController::getInstance().getMousePosition().getState();
	glm::vec2 mousePosOld = InputController::getInstance().getMousePosition().getOldState();

	float diffX = (float)(mousePos.x - mousePosOld.x);
	float diffY = (float)(mousePosOld.y - mousePos.y);

	if (diffX != 0 || diffY != 0)
	{
		diffX *= this->mouseSensitivity;
		diffY *= this->mouseSensitivity;

		this->yaw += diffX;
		this->pitch += diffY;

		this->pitch = glm::clamp(this->pitch, -90.0f, 90.0f);

		float pitchRad = glm::radians(this->pitch);
		float yawRad = glm::radians(this->yaw);

		float cosPitch = cos(pitchRad);
		float sinPitch = sin(pitchRad);
		float cosYaw = cos(yawRad);
		float sinYaw = sin(yawRad);
		glm::vec3 cameraFront = glm::vec3(cosPitch * cosYaw, sinPitch, cosPitch * sinYaw);

		camera->setTarget(cameraFront);
	}
}
void CameraController::handleMouseMove(Camera* camera)
{
	float actualSpeed = Game::getInstance().getDeltaTime() * this->cameraSpeed;

	if (InputController::getInstance().isButtonPressed(GLFW_KEY_D))
	{
		camera->getGameObject()->getTransform().moveBy(-camera->getLeft() * actualSpeed);
	}
	if (InputController::getInstance().isButtonPressed(GLFW_KEY_A))
	{
		camera->getGameObject()->getTransform().moveBy(camera->getLeft() * actualSpeed);
	}
	if (InputController::getInstance().isButtonPressed(GLFW_KEY_W))
	{
		camera->getGameObject()->getTransform().moveBy(camera->getFront() * actualSpeed);
	}
	if (InputController::getInstance().isButtonPressed(GLFW_KEY_S))
	{
		camera->getGameObject()->getTransform().moveBy(-camera->getFront() * actualSpeed);
	}
}