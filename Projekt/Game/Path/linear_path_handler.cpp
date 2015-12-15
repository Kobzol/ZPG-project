#include "linear_path_handler.h"
#include "../game.h"

LinearPathHandler::LinearPathHandler(std::initializer_list<glm::vec3> points, float speed, size_t startPoint) : points(points),  currentDelta(0.0f), currentPoint(startPoint)
{
	if (points.size() < 2)
	{
		throw std::exception("At least two points have to be specified");
	}

	this->delta = speed / 60.0f;
}

void LinearPathHandler::move(Transform& transform)
{
	size_t nextPoint = (this->currentPoint + 1) % this->points.size();

	float delta = this->delta;// *Game::getInstance().getDeltaTime();

	glm::vec3 direction = this->points[nextPoint] - this->points[this->currentPoint];
	direction *= delta;

	transform.moveBy(direction);

	this->currentDelta += delta;

	if (this->currentDelta >= 1.0f)
	{
		this->currentPoint = (this->currentPoint + 1) % this->points.size();
		this->currentDelta = 0.0f;
	}
}