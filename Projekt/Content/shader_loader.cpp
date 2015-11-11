#include "shader_loader.h"

ShaderLoader ShaderLoader::instance = ShaderLoader();

ShaderLoader& ShaderLoader::getInstance()
{
	return ShaderLoader::instance;
}

ShaderLoader::ShaderLoader()
{

}

Shader ShaderLoader::createShader(std::string code, GLenum type)
{
	GLenum shaderId = glCreateShader(type);

	this->preprocessCode(code);

	const GLchar* codePointer = code.c_str();

	glShaderSource(shaderId, 1, &codePointer, nullptr);
	glCompileShader(shaderId);

	GL_CHECK_COMPILATION(shaderId);
	GL_CHECK_ERRORS();

	return Shader(shaderId);
}

void ShaderLoader::addCodeMapping(const std::string& directive, const std::string& replacement)
{
	this->codeMappings.emplace(directive, replacement);
}

void ShaderLoader::preprocessCode(std::string& code)
{
	for (auto mapping : this->codeMappings)
	{
		size_t position = code.find(mapping.first);

		if (position != std::string::npos)
		{
			code.replace(position, mapping.first.size(), mapping.second);
		}
	}
}