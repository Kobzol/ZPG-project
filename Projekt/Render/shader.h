#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#include <string>

#include "../Helper/opengl_helper.h"

class Shader
{
private:
	GLuint shader;

public:
	Shader(GLuint shader);

	GLuint getId();
	void dispose();
};