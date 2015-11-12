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

Program::Program(Flags<ProgramEvent> events) : events(events)
{
	this->program = glCreateProgram();
	GL_CHECK_ERRORS();
}

void Program::attachShader(Shader& shader)
{
	glAttachShader(this->program, shader.getId());
	GL_CHECK_ERRORS();

	this->shaders.push_back(shader);
}
void Program::link()
{
	glLinkProgram(this->program);
	GL_CHECK_LINKAGE(this->program);
	GL_CHECK_ERRORS();

	for (Shader& shader : this->shaders)
	{
		glDetachShader(this->program, shader.getId());
		GL_CHECK_ERRORS();
		shader.dispose();
	}

	this->shaders.clear();
}
void Program::dispose()
{
	glDeleteProgram(this->program);
	GL_CHECK_ERRORS();
}
void Program::use()
{
	glUseProgram(this->program);
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
	GLint location = this->getUniformLocation(name);

	if (location < 0)
	{
		return;
	}

	glUniform4f(location, value.x, value.y, value.z, value.a);
	GL_CHECK_ERRORS();
}
void Program::setUniform3f(std::string name, GLfloat x, GLfloat y, GLfloat z)
{
	GLint location = this->getUniformLocation(name);

	if (location < 0)
	{
		return;
	}

	glUniform3f(location, x, y, z);
	GL_CHECK_ERRORS();
}
void Program::setUniform3f(std::string name, glm::vec3 value)
{
	this->setUniform3f(name, value.x, value.y, value.z);
}
void Program::setUniform2f(std::string name, glm::vec2 value)
{
	GLint location = this->getUniformLocation(name);

	if (location < 0)
	{
		return;
	}

	glUniform2f(location, value.x, value.y);
	GL_CHECK_ERRORS();
}
void Program::setUniform1f(std::string name, GLfloat value)
{
	GLint location = this->getUniformLocation(name);

	if (location < 0)
	{
		return;
	}

	glUniform1f(location, value);
	GL_CHECK_ERRORS();
}
void Program::setUniform1i(std::string name, GLint value)
{
	GLint location = this->getUniformLocation(name);

	if (location < 0)
	{
		return;
	}

	glUniform1i(location, value);
	GL_CHECK_ERRORS();
}
void Program::setUniformMatrix3fv(std::string name, const glm::mat3& matrix)
{
	GLint location = this->getUniformLocation(name);

	if (location < 0)
	{
		return;
	}

	glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	GL_CHECK_ERRORS();
}
void Program::setUniformMatrix4fv(std::string name, const glm::mat4& matrix)
{
	GLint location = this->getUniformLocation(name);

	if (location < 0)
	{
		return;
	}

	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	GL_CHECK_ERRORS();
}

void Program::setViewMatrix(const glm::mat4& matrix)
{
	this->setUniformMatrix4fv("viewMatrix", matrix);
}
void Program::setProjectionMatrix(const glm::mat4& matrix)
{
	this->setUniformMatrix4fv("projectionMatrix", matrix);
}
void Program::setModelMatrix(const glm::mat4& matrix, bool setNormalMatrix)
{
	this->setUniformMatrix4fv("modelMatrix", matrix);

	if (setNormalMatrix)
	{
		this->setUniformMatrix3fv("normalMatrix", glm::mat3(glm::transpose(glm::inverse(matrix))));
	}
}
void Program::setViewPosition(const glm::vec3& position)
{
	this->setUniform3f("viewPosition", position);
}
void Program::setLightSpaceMatrix(const glm::mat4& matrix)
{
	this->setUniformMatrix4fv("lightSpaceMatrix", matrix);
}

Flags<ProgramEvent> Program::getEvents()
{
	return this->events;
}