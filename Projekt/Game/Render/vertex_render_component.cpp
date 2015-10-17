#include "vertex_render_component.h"

VertexRenderComponent::VertexRenderComponent(const Vertex* data, size_t verticesCount) : verticesCount(verticesCount)
{
	this->vao.bind();

	this->vbo.bind();
	this->vbo.setData(data, sizeof(Vertex) * verticesCount, GL_STATIC_DRAW);

	Program::setAttribute(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*) offsetof(Vertex, position));
	Program::setAttribute(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*) offsetof(Vertex, normal));

	this->vao.unbind();
}

void VertexRenderComponent::update()
{
	Transform& transform = this->gameObject->getTransform();

	if (transform.isDirty())
	{
		ProgramManager::getInstance().getCurrentProgram().setModelMatrix(this->gameObject->getTransform().getModel());
		transform.clearDirty({ TransformDirtyBit::Position, TransformDirtyBit::Rotation, TransformDirtyBit::Scale });
	}

	this->vao.bind();
	RenderUtils::drawTriangles(0, this->verticesCount);
	this->vao.unbind();
}
void VertexRenderComponent::dispose()
{
	this->vbo.dispose();
	this->vao.dispose();
}