#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#include "../Helper/opengl_helper.h"

class EBO
{
private:
	GLuint ebo;

public:
	EBO();

	GLuint getId();
	void setData(void* data, GLint size, GLenum mode = GL_STATIC_DRAW);

	void bind();
	void dispose();
};