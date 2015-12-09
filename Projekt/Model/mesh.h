#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#include <glm/glm.hpp>

#include <string>
#include <vector>

#include "../Buffer/ebo.h"
#include "../Content/program_Manager.h"
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

	Mesh(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices, const std::vector<Texture>& textures);

	void setup();

	glm::vec4 getColor() const;
	void setColor(glm::vec4 color);

	void draw();
	void dispose();

private:
	Mesh& operator=(const Mesh& other);

	VAO vao;
	VBO vbo;
	EBO ebo;

	glm::vec4 color;
};