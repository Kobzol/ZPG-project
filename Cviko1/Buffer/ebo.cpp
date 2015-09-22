#include "ebo.h"

EBO::EBO()
{
	glGenBuffers(1, &this->ebo);
	GL_CHECK_ERRORS();
}

void EBO::bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
	GL_CHECK_ERRORS();
}
void EBO::free()
{
	glDeleteBuffers(GL_ELEMENT_ARRAY_BUFFER, &this->ebo);
	GL_CHECK_ERRORS();
	this->ebo = 0;
}

GLuint EBO::getId()
{
	return this->ebo;
}

void EBO::setData(void* data, GLint size, GLenum mode)
{
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, mode);
	GL_CHECK_ERRORS();
}