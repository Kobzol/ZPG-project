#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#include "program.h"

class Renderer
{
public:
	Renderer();

	void clear(GLbitfield mask);
	void clearColor(GLclampf r, GLclampf g, GLclampf b, GLclampf a);;

	void drawTriangles(GLint skip, GLsizei verticesCount);
	void drawTriangles(Program& program, GLint skip, GLsizei verticesCount);

	void drawElements(GLsizei indicesCount, GLenum dataType, void* offset);
	void drawElements(Program& program, GLsizei indicesCount, GLenum dataType, void* offset);
	
	void drawPoints(GLint skip, GLsizei pointsCount);

	void drawTriangleStrip(GLint skip, GLsizei verticesCount);
};