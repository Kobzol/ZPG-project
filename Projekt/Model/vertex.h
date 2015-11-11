#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

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

#pragma region vertices
const VertexSimple VERTICES_CUBE[] = {
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

static GLfloat VERTICES_SKYBOX[] = {
	// Positions          
	-1.0f, 1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, 1.0f, -1.0f,
	-1.0f, 1.0f, -1.0f,

	-1.0f, -1.0f, 1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f, 1.0f, -1.0f,
	-1.0f, 1.0f, -1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, -1.0f, 1.0f,

	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,

	-1.0f, -1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, -1.0f, 1.0f,
	-1.0f, -1.0f, 1.0f,

	-1.0f, 1.0f, -1.0f,
	1.0f, 1.0f, -1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, -1.0f,

	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f, 1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f, 1.0f,
	1.0f, -1.0f, 1.0f
};

static GLfloat VERTICES_SPRITE[] = {
	// Pos      // Tex
	0.0f, 1.0f, 0.0f, 1.0f,
	1.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 0.0f,

	0.0f, 1.0f, 0.0f, 1.0f,
	1.0f, 1.0f, 1.0f, 1.0f,
	1.0f, 0.0f, 1.0f, 0.0f
};

static VertexSimple VERTICES_PLANE[] = {
	{ { -1.0f, 0.0f, 1.0f } },
	{ { 1.0f, 0.0f, 1.0f } },
	{ { 1.0f, 0.0f, -1.0f } },
	{ { 1.0f, 0.0f, -1.0f } },
	{ { -1.0f, 0.0f, -1.0f } },
	{ { -1.0f, 0.0f, 1.0f } }
};
#pragma endregion vertices