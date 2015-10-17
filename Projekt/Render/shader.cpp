#include "shader.h"

Shader::Shader(std::string code, GLenum type)
{
	this->shader = glCreateShader(type);

	const GLchar* codePointer = code.c_str();

	glShaderSource(this->shader, 1, &codePointer, nullptr);
	glCompileShader(this->shader);

	GL_CHECK_COMPILATION(this->shader);
	GL_CHECK_ERRORS();
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