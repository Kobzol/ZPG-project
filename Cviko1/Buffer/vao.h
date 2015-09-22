#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#include "../Helper/helper.h"

class VAO
{
private:
	GLuint vao;

public:
	static void enable(int index);

	VAO();

	GLuint getId();

	void bind();
	void unbind();
	void free();
};