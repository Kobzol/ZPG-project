#pragma once

#include "../Buffer/vao.h"
#include "../Buffer/vbo.h"
#include "../Render/program.h"

class GeometryObject
{
public:
	GeometryObject();
	GeometryObject(const void* data, size_t vertexSize, size_t vertexCount);

	void setGeometry(const void* data, size_t vertexSize, size_t vertexCount);

	void setAttributePosition();

	void dispose();

	VAO getVAO();
	VBO getVBO();
	size_t getVertexCount();

private:
	VBO vbo;
	VAO vao;

	size_t vertexCount;
	size_t vertexSize;
};