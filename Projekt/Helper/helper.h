#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#include <string>
#include <iostream>

#define GL_CHECK_ERRORS() gl_check_error(__FILE__, __LINE__);
#define GL_CHECK_COMPILATION(shader) gl_check_compilation(shader, __FILE__, __LINE__);
#define GL_CHECK_LINKAGE(program) gl_check_linkage(program, __FILE__, __LINE__);
#define GL_PRINT_ERROR(message) gl_print_error(message, __FILE__, __LINE__);

static void gl_print_error(std::string message, const char* filename, int line)
{
	std::cerr << "OpenGL Error: " << message << " in " << filename << ":" << line << std::endl;
}
static void gl_clear_error()
{
	glGetError();
}
static void gl_check_error(const char* filename, int line)
{
	GLenum error = glGetError();

	if (error != GL_NO_ERROR)
	{
		std::string message;
		switch (error)
		{
		case GL_INVALID_ENUM:
			message = "GL_INVALID_ENUM";
			break;
		case GL_INVALID_VALUE:
			message = "GL_INVALID_VALUE";
			break;
		case GL_INVALID_OPERATION:
			message = "GL_INVALID_OPERATION";
			break;
		case GL_STACK_OVERFLOW:
			message = "GL_STACK_OVERFLOW";
			break;
		case GL_STACK_UNDERFLOW:
			message = "GL_STACK_UNDERFLOW";
			break;
		case GL_OUT_OF_MEMORY:
			message = "GL_OUT_OF_MEMORY";
			break;
		default:
			message = "UNKNOWN_ERROR";
			break;
		}

		gl_print_error(message, filename, line);
	}
}
static void gl_check_compilation(GLuint shader, const char* filename, int line)
{
	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

	if (status != GL_TRUE)
	{
		char buffer[512];
		glGetShaderInfoLog(shader, sizeof(buffer), nullptr, buffer);

		gl_print_error(std::string(buffer), filename, line);
	}
}
static void gl_check_linkage(GLuint program, const char* filename, int line)
{
	GLint status;
	glGetProgramiv(program, GL_LINK_STATUS, &status);

	if (status != GL_TRUE)
	{
		char buffer[512];
		glGetProgramInfoLog(program, sizeof(buffer), nullptr, buffer);

		gl_print_error(std::string(buffer), filename, line);
	}
}