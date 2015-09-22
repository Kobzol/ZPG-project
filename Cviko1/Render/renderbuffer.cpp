#include "renderbuffer.h"

Renderbuffer::Renderbuffer()
{
	glGenRenderbuffers(1, &this->renderbuffer);
	GL_CHECK_ERRORS();
}
Renderbuffer::~Renderbuffer()
{
	glDeleteRenderbuffers(1, &this->renderbuffer);
	GL_CHECK_ERRORS();
}

void Renderbuffer::bind()
{
	glBindRenderbuffer(GL_RENDERBUFFER, this->renderbuffer);
	GL_CHECK_ERRORS();
}

void Renderbuffer::setStorage(GLenum type, GLsizei width, GLsizei height)
{
	glRenderbufferStorage(GL_RENDERBUFFER, type, width, height);
	GL_CHECK_ERRORS();
}

GLuint Renderbuffer::getId()
{
	return this->renderbuffer;
}