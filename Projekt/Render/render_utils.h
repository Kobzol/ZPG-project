#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#include "program.h"

class RenderUtils
{
public:
	static void clear(GLbitfield mask);
	static void clearColor(GLclampf r, GLclampf g, GLclampf b, GLclampf a);

	static void drawTriangles(GLint skip, GLsizei verticesCount);

	static void drawElements(GLsizei indicesCount, GLenum dataType, void* offset);
	
	static void drawPoints(GLint skip, GLsizei pointsCount);

	static void drawTriangleStrip(GLint skip, GLsizei verticesCount);

private:
	RenderUtils();
};