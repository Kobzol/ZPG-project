#pragma once

#include <glm/glm.hpp>

class MouseState
{
public:
	MouseState();

	glm::vec2 getState();
	glm::vec2 getOldState();

	void update(float x, float y);
	void resetOldState();

private:
	bool firstEvent;

	glm::vec2 state;
	glm::vec2 oldState;
};