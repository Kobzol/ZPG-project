#pragma once

#include <glm/glm.hpp>

struct Vertex
{
public:
	glm::vec3 position;

	Vertex();
	Vertex(const glm::vec3& position);
};