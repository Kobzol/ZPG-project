#include "geometry_object.h"


GeometryObject::GeometryObject() : vertexSize(0), vertexCount(0)
{

}
GeometryObject::GeometryObject(const void* data, size_t vertexSize, size_t vertexCount)
{
	this->setGeometry(data, vertexSize, vertexCount);
}

void GeometryObject::setGeometry(const void* data, size_t vertexSize, size_t vertexCount)
{
	this->vertexSize = vertexSize;
	this->vertexCount = vertexCount;

	this->vao.bind();

	this->vbo.bind();
	this->vbo.setData(data, vertexSize * vertexCount, GL_STATIC_DRAW);

	this->vao.unbind();
}

void GeometryObject::setAttributePosition()
{
	this->vao.bind();
	Program::setAttribute(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
	this->vao.unbind();
}
void GeometryObject::setAttributePositionTexture2D()
{
	this->vao.bind();
	Program::setAttribute(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	Program::setAttribute(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*) (2 * sizeof(GLfloat)));
	this->vao.unbind();
}
void GeometryObject::setAttributePositionNormal()
{
	this->vao.bind();
	Program::setAttribute(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
	Program::setAttribute(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	this->vao.unbind();
}

void GeometryObject::dispose()
{
	this->vao.dispose();
	this->vbo.dispose();
}

VAO GeometryObject::getVAO()
{
	return this->vao;
}
VBO GeometryObject::getVBO()
{
	return this->vbo;
}
size_t GeometryObject::getVertexCount()
{
	return this->vertexCount;
}