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

	Shader(const Shader& other);
	Shader& operator=(Shader& other);

public:
	Shader(std::string code, GLenum type);
	~Shader();

	GLuint getId();
};