#include "program.h"

void Program::setAttribute(GLint position, GLint count, GLenum type, GLboolean normalize, GLsizei stride, const void* offset)
{
	glVertexAttribPointer(position, count, type, normalize, stride, offset);
	VAO::enable(position);

	GL_CHECK_ERRORS();
}

Program::Program()
{
	this->program = glCreateProgram();
	GL_CHECK_ERRORS();
}

void Program::attachShader(Shader& shader)
{
	glAttachShader(this->program, shader.getId());
	GL_CHECK_ERRORS();
}
void Program::link()
{
	glLinkProgram(this->program);
	GL_CHECK_LINKAGE(this->program);
	GL_CHECK_ERRORS();
}
void Program::use()
{
	glUseProgram(this->program);

	GL_CHECK_ERRORS();
}
void Program::free()
{
	glDeleteProgram(this->program);
	GL_CHECK_ERRORS();
}

GLint Program::getAttributeLocation(std::string name)
{
	GLint location = glGetAttribLocation(this->program, name.c_str());
	
	GL_CHECK_ERRORS();
	
	return location;
}
void Program::setAttribute(std::string name, GLint count, GLenum type, GLboolean normalize, GLsizei stride, const void * offset)
{
	Program::setAttribute(this->getAttributeLocation(name), count, type, normalize, stride, offset);
}

GLint Program::getUniformLocation(std::string name)
{
	GLint location = glGetUniformLocation(this->program, name.c_str());

	GL_CHECK_ERRORS();

	return location;
}
void Program::setUniform4f(std::string name, const glm::vec4& value)
{
	glUniform4f(this->getUniformLocation(name), value.x, value.y, value.z, value.a);
	GL_CHECK_ERRORS();
}
void Program::setUniform3f(std::string name, GLfloat x, GLfloat y, GLfloat z)
{
	glUniform3f(this->getUniformLocation(name), x, y, z);
	GL_CHECK_ERRORS();
}
void Program::setUniform3f(std::string name, glm::vec3 value)
{
	this->setUniform3f(name, value.x, value.y, value.z);
}
void Program::setUniform2f(std::string name, glm::vec2 value)
{
	glUniform2f(this->getUniformLocation(name), value.x, value.y);
	GL_CHECK_ERRORS();
}
void Program::setUniform1f(std::string name, GLfloat value)
{
	glUniform1f(this->getUniformLocation(name), value);
	GL_CHECK_ERRORS();
}
void Program::setUniform1i(std::string name, GLint value)
{
	glUniform1i(this->getUniformLocation(name), value);
	GL_CHECK_ERRORS();
}
void Program::setUniformMatrix4fv(std::string name, const glm::mat4& matrix)
{
	glUniformMatrix4fv(this->getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
	GL_CHECK_ERRORS();
}

void Program::notifyCameraChanged(Camera& camera)
{
	this->setCameraMatrices(camera);
}
void Program::setCameraMatrices(Camera& camera)
{
	this->setUniformMatrix4fv("View", camera.getViewMatrix());
	this->setUniformMatrix4fv("Projection", camera.getProjectionMatrix());
}