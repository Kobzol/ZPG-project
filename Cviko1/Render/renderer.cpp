#include "renderer.h"

Renderer::Renderer()
{

}

void Renderer::clear(GLbitfield mask)
{
	glClear(mask);
	GL_CHECK_ERRORS();
}
void Renderer::clearColor(GLclampf r, GLclampf g, GLclampf b, GLclampf a)
{
	glClearColor(r, g, b, a);
	GL_CHECK_ERRORS();
}

void Renderer::drawTriangles(GLint skip, GLsizei verticesCount)
{
	glDrawArrays(GL_TRIANGLES, skip, verticesCount);
	GL_CHECK_ERRORS();
}
void Renderer::drawTriangles(Program& program, GLint skip, GLsizei verticesCount)
{
	program.use();
	this->drawTriangles(skip, verticesCount);
}

void Renderer::drawElements(GLsizei indicesCount, GLenum dataType, void* offset)
{
	glDrawElements(GL_TRIANGLES, indicesCount, dataType, offset);
	GL_CHECK_ERRORS();
}
void Renderer::drawElements(Program& program, GLsizei indicesCount, GLenum dataType, void* offset)
{
	program.use();
	this->drawElements(indicesCount, dataType, offset);
}

void Renderer::drawPoints(GLint skip, GLsizei pointsCount)
{
	glDrawArrays(GL_POINTS, skip, pointsCount);
	GL_CHECK_ERRORS();
}

void Renderer::drawTriangleStrip(GLint skip, GLsizei verticesCount)
{
	glDrawArrays(GL_TRIANGLE_STRIP, skip, verticesCount);
	GL_CHECK_ERRORS();
}