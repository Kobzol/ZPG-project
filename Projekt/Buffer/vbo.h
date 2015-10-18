#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#include "../Model/vertex.h"

#include "../Helper/opengl_helper.h"

class VBO
{
private:
	GLuint vbo;

public:
	VBO();

	GLuint getId();
	void setData(const void* data, GLint size, GLenum mode = GL_STATIC_DRAW);

	void bind();
	void unbind();
	void dispose();
};