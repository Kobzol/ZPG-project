#pragma once

#include <glm/glm.hpp>

struct Vertex
{
public:
	glm::vec3 position;
	glm::vec3 normal;

	Vertex();
	Vertex(glm::vec3 position, glm::vec3 normal);
};