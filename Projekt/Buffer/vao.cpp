#include "vao.h"

void VAO::enable(int index)
{
	glEnableVertexAttribArray(index);
	GL_CHECK_ERRORS();
}

VAO::VAO()
{
	glGenVertexArrays(1, &this->vao);
	GL_CHECK_ERRORS();
}

GLuint VAO::getId()
{
	return this->vao;
}

void VAO::bind()
{
	glBindVertexArray(this->vao); 
	GL_CHECK_ERRORS();
}
void VAO::unbind()
{
	glBindVertexArray(0);
	GL_CHECK_ERRORS();
}
void VAO::dispose()
{
	glDeleteVertexArrays(1, &this->vao);
	GL_CHECK_ERRORS();
	this->vao = 0;
}