#include "shader.h"

Shader::Shader(GLuint shader) : shader(shader)
{
	
}

void Shader::dispose()
{
	glDeleteShader(this->shader);
	GL_CHECK_ERRORS();
}

GLuint Shader::getId()
{
	return this->shader;
}