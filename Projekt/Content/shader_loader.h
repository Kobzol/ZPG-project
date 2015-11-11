#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#include <unordered_map>

#include "../Helper/opengl_helper.h"
#include "../Render/shader.h"

class ShaderLoader
{
public:
	static ShaderLoader& getInstance();

	Shader createShader(std::string code, GLenum type);
	void addCodeMapping(const std::string& directive, const std::string& replacement);

private:
	static ShaderLoader instance;

	ShaderLoader();

	void preprocessCode(std::string& code);

	std::unordered_map<std::string, std::string> codeMappings;
};