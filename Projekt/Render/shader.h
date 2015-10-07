#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#include <string>

#include "../Helper/helper.h"

class Shader
{
private:
	GLuint shader;
	GLint type;

public:
	Shader(std::string code, GLenum type);

	GLuint getId();
	void free();
};