#include "shader_loader.h"

ShaderLoader ShaderLoader::instance = ShaderLoader();

ShaderLoader& ShaderLoader::getInstance()
{
	return ShaderLoader::instance;
}

ShaderLoader::ShaderLoader()
{

}

std::string ShaderLoader::preprocessCode(const std::string& code)
{
	return code;
}

Shader ShaderLoader::createShader(std::string code, GLenum type)
{
	GLenum shaderId = glCreateShader(type);

	code = this->preprocessCode(code);

	const GLchar* codePointer = code.c_str();

	glShaderSource(shaderId, 1, &codePointer, nullptr);
	glCompileShader(shaderId);

	GL_CHECK_COMPILATION(shaderId);
	GL_CHECK_ERRORS();

	return Shader(shaderId);
}