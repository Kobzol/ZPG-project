#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#include "../Helper/opengl_helper.h"

class Renderbuffer
{
private:
	GLuint renderbuffer;

public:
	Renderbuffer();

	GLuint getId();

	void bind();
	void dispose();

	void setStorage(GLenum type, GLsizei width, GLsizei height);
};