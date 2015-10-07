#pragma once

#include <glm/glm.hpp>

struct Vertex
{
public:
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoords;

	Vertex();
	Vertex(const glm::vec3& position, const glm::vec3& normal, const glm::vec2& texCoords);
};