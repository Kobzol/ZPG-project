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
	Shader(std::string code, GLenum type);

	GLuint getId();
	void dispose();
};