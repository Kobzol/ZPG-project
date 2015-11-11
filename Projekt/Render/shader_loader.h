#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#include "shader.h"
#include "../Helper/opengl_helper.h"

class ShaderLoader
{
public:
	static ShaderLoader& getInstance();

	Shader createShader(std::string code, GLenum type);

private:
	static ShaderLoader instance;

	std::string preprocessCode(const std::string& code);

	ShaderLoader();
};