#pragma once

#include <glm/glm.hpp>

#include <cmath>
#include <vector>

#include "ipath_handler.h"

class BezierPathHandler : public IPathHandler
{
public:
	BezierPathHandler(std::initializer_list<glm::vec3> points, float speed = 1.0f);

	virtual void move(Transform& transform) override;
	virtual bool isFinished() override;
	virtual void reset() override;

private:
	double calculateBernstein(int n, int i, double t);
	uint64_t calculateCombinatorialNumber(int n, int k);
	glm::vec3 calculatePoint(double t);

	std::vector<glm::vec3> points;
	float delta;
	float speed;
};