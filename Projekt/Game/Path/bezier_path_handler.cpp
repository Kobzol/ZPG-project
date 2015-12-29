#include "bezier_path_handler.h"

BezierPathHandler::BezierPathHandler(std::initializer_list<glm::vec3> points, float speed) : points(points), delta(0.0f), speed(speed)
{

}

void BezierPathHandler::move(Transform& transform)
{
	glm::vec3 point = this->calculatePoint(1.0f);

	transform.setPosition(this->calculatePoint(this->delta));
	this->delta += this->speed / 60.0f;
}
bool BezierPathHandler::isFinished()
{
	return this->delta >= 1.0f;
}
void BezierPathHandler::reset()
{
	this->delta = 0.0f;
}

double BezierPathHandler::calculateBernstein(int n, int i, double t)
{
	uint64_t comb = this->calculateCombinatorialNumber(n, i);
	
	double exp = pow(t, (double) i);
	double exp2 = pow(1.0 - t, n - i);

	return comb * exp * exp2;
}
uint64_t BezierPathHandler::calculateCombinatorialNumber(int n, int k)
{
	if (k == 0 || k == n) return 1;
	
	uint64_t top = 1;

	for (int i = k + 1; i <= n; i++)
	{
		top *= i;
	}

	uint64_t bottom = 1;

	for (int i = 1; i <= (n - k); i++)
	{
		bottom *= i;
	}

	return top / bottom;
}
glm::vec3 BezierPathHandler::calculatePoint(double t)
{
	glm::vec3 point = glm::vec3(0.0f);
	int n = this->points.size() - 1;

	for (size_t i = 0; i < this->points.size(); i++)
	{
		point += this->points[i] * (float) this->calculateBernstein(n, i, t);
	}

	return point;
}