#pragma once

#include <glm/glm.hpp>

#include <exception>
#include <vector>

#include "ipath_handler.h"

class LinearPathHandler : public IPathHandler
{
public:
	LinearPathHandler(std::initializer_list<glm::vec3> points, float speed = 1.0f, size_t startPoint = 0);

	virtual void move(Transform& transform) override;
	virtual bool isFinished() override;
	virtual void reset() override;

private:
	std::vector<glm::vec3> points;
	size_t currentPoint;
	float delta;
	float currentDelta;
};