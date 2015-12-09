#include "render_utils.h"
#include "../Game/Render/render_component.h"

RenderUtils::RenderUtils()
{

}

void RenderUtils::clear(GLbitfield mask)
{
	glClear(mask);
	GL_CHECK_ERRORS();
}
void RenderUtils::clearColor(GLclampf r, GLclampf g, GLclampf b, GLclampf a)
{
	glClearColor(r, g, b, a);
	GL_CHECK_ERRORS();
}

void RenderUtils::drawTriangles(GLint skip, GLsizei verticesCount)
{
	glDrawArrays(GL_TRIANGLES, skip, verticesCount);
	GL_CHECK_ERRORS();
}

void RenderUtils::drawElements(GLsizei indicesCount, GLenum dataType, void* offset)
{
	glDrawElements(GL_TRIANGLES, indicesCount, dataType, offset);
	GL_CHECK_ERRORS();
}

void RenderUtils::drawPoints(GLint skip, GLsizei pointsCount)
{
	glDrawArrays(GL_POINTS, skip, pointsCount);
	GL_CHECK_ERRORS();
}

void RenderUtils::drawTriangleStrip(GLint skip, GLsizei verticesCount)
{
	glDrawArrays(GL_TRIANGLE_STRIP, skip, verticesCount);
	GL_CHECK_ERRORS();
}

IComponent* RenderUtils::createCubeRenderer(glm::vec3 color)
{
	GeometryObject cubeGeometry(VERTICES_CUBE, sizeof(glm::vec3), 36);
	cubeGeometry.setAttributePosition();
	return new RenderComponent(color, ProgramManager::PROGRAM_GEOMETRY_CONSTANT, new GeometryDrawModule(cubeGeometry));
}