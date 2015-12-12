#include "vertex.h"

Vertex::Vertex()
{

}
Vertex::Vertex(glm::vec3 position, glm::vec3 normal, glm::vec2 texCoords, glm::vec3 tangent)
	: position(position), normal(normal), texCoords(texCoords), tangent(tangent)
{

}

VertexHeightMap::VertexHeightMap()
{

}
VertexHeightMap::VertexHeightMap(glm::vec3 position, glm::vec2 texCoords)
	: position(position), texCoords(texCoords)
{

}