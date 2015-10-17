#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#include <string>
#include <vector>

#include "../Buffer/ebo.h"
#include "../Game/Content/program_Manager.h"
#include "../Render/render_utils.h"
#include "../Buffer/vao.h"
#include "../Buffer/vbo.h"
#include "texture.h"
#include "vertex.h"

class Mesh
{
public:
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Texture> textures;

	Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures);

	void setup();

	void draw();
	void free();

private:
	VAO vao;
	VBO vbo;
	EBO ebo;
};