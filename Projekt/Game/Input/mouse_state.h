#pragma once

#include <glm/glm.hpp>

class MouseState
{
public:
	glm::vec2 getState();
	glm::vec2 getOldState();

	void update(float x, float y);

private:
	bool firstEvent;

	glm::vec2 state;
	glm::vec2 oldState;
};