#include "vertex.h"

Vertex::Vertex()
{

}
Vertex::Vertex(const glm::vec3& position, const glm::vec3& normal, const glm::vec2& texCoords)
	: position(position), normal(normal), texCoords(texCoords)
{

}