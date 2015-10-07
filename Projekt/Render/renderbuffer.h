#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#include "../Helper/opengl_helper.h"

class Renderbuffer
{
private:
	GLuint renderbuffer;

	Renderbuffer(const Renderbuffer& other);
	Renderbuffer& operator=(Renderbuffer& other);

public:
	Renderbuffer();
	~Renderbuffer();

	GLuint getId();

	void bind();

	void setStorage(GLenum type, GLsizei width, GLsizei height);
};