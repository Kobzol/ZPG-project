#include "mouse_state.h"

MouseState::MouseState() : firstEvent(true)
{

}

glm::vec2 MouseState::getState()
{
	return this->state;
}
glm::vec2 MouseState::getOldState()
{
	return this->oldState;
}

void MouseState::update(float x, float y)
{
	if (this->firstEvent)
	{
		this->oldState = this->state = glm::vec2(x, y);
		this->firstEvent = false;

		return;
	}

	this->oldState = this->state;
	this->state = glm::vec2(x, y);
}
void MouseState::resetOldState()
{
	this->oldState = this->state;
}