#pragma once

#include <glm/glm.hpp>

struct VertexSimple
{
public:
	glm::vec3 position;
};

struct Vertex
{
public:
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoords;

	Vertex();
	Vertex(glm::vec3 position, glm::vec3 normal, glm::vec2 texCoords);
};

const VertexSimple VERTEX_CUBE[] = {
	// back face
	{ { -0.5f, -0.5f, -0.5f } },
	{ { -0.5f, 0.5f, -0.5f } },
	{ { 0.5f, 0.5f, -0.5f } },
	{ { 0.5f, 0.5f, -0.5f } },
	{ { 0.5f, -0.5f, -0.5f } },
	{ { -0.5f, -0.5f, -0.5f } },

	// front face
	{ { -0.5f, -0.5f, 0.5f } },
	{ { 0.5f, -0.5f, 0.5f } },
	{ { 0.5f, 0.5f, 0.5f } },
	{ { 0.5f, 0.5f, 0.5f } },
	{ { -0.5f, 0.5f, 0.5f } },
	{ { -0.5f, -0.5f, 0.5f } },

	// left face
	{ { -0.5f, 0.5f, 0.5f } },
	{ { -0.5f, 0.5f, -0.5f } },
	{ { -0.5f, -0.5f, -0.5f } },
	{ { -0.5f, -0.5f, -0.5f } },
	{ { -0.5f, -0.5f, 0.5f } },
	{ { -0.5f, 0.5f, 0.5f } },

	// right face
	{ { 0.5f, 0.5f, 0.5f } },
	{ { 0.5f, -0.5f, 0.5f } },
	{ { 0.5f, -0.5f, -0.5f } },
	{ { 0.5f, -0.5f, -0.5f } },
	{ { 0.5f, 0.5f, -0.5f } },
	{ { 0.5f, 0.5f, 0.5f } },

	// down face
	{ { -0.5f, -0.5f, -0.5f } },
	{ { 0.5f, -0.5f, -0.5f } },
	{ { 0.5f, -0.5f, 0.5f } },
	{ { 0.5f, -0.5f, 0.5f } },
	{ { -0.5f, -0.5f, 0.5f } },
	{ { -0.5f, -0.5f, -0.5f } },

	// up face
	{ { -0.5f, 0.5f, -0.5f } },
	{ { -0.5f, 0.5f, 0.5f } },
	{ { 0.5f, 0.5f, 0.5f } },
	{ { 0.5f, 0.5f, 0.5f } },
	{ { 0.5f, 0.5f, -0.5f } },
	{ { -0.5f, 0.5f, -0.5f } }
};