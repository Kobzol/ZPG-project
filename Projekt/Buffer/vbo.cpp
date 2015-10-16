#include "vbo.h"

VBO::VBO()
{
	glGenBuffers(1, &this->vbo);
	GL_CHECK_ERRORS();
}

void VBO::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	GL_CHECK_ERRORS();
}
void VBO::unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	GL_CHECK_ERRORS();
}
void VBO::dispose()
{
	glDeleteBuffers(GL_ARRAY_BUFFER, &this->vbo); // crashes
	GL_CHECK_ERRORS();
	this->vbo = 0;
}

GLuint VBO::getId()
{
	return this->vbo;
}

void VBO::setData(const Vertex* data, GLint size, GLenum mode)
{
	glBufferData(GL_ARRAY_BUFFER, size, data, mode);
	GL_CHECK_ERRORS();
}