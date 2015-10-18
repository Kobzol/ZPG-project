#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <memory>
#include <string>
#include <vector>

#include "shader.h"
#include "../Buffer/vao.h"
#include "../Helper/opengl_helper.h"

class ProgramManager;

class Program
{
	friend class ProgramManager;

private:
	void use();

	std::vector<Shader> shaders;
	GLuint program;

public:
	static void setAttribute(GLint position, GLint count, GLenum type, GLboolean normalize, GLsizei stride, const void* offset);

	Program();

	void attachShader(Shader& shader);
	void link();
	void dispose();

	GLint getAttributeLocation(std::string name);
	void setAttribute(std::string name, GLint count, GLenum type, GLboolean normalize, GLsizei stride, const void* offset);

	GLint getUniformLocation(std::string name);
	void setUniform4f(std::string name, const glm::vec4& value);
	void setUniform3f(std::string name, GLfloat x, GLfloat y, GLfloat z);
	void setUniform3f(std::string name, glm::vec3 value);
	void setUniform2f(std::string name, glm::vec2 value);
	void setUniform1f(std::string name, GLfloat value);
	void setUniform1i(std::string name, GLint value);
	void setUniformMatrix3fv(std::string name, const glm::mat3& matrix);
	void setUniformMatrix4fv(std::string name, const glm::mat4& matrix);

	void setViewMatrix(const glm::mat4& matrix);
	void setProjectionMatrix(const glm::mat4& matrix);
	void setModelMatrix(const glm::mat4& matrix);

	VAO* getVAO();
};