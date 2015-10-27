#include "simple_constant_renderer.h"

SimpleConstantRenderer::SimpleConstantRenderer(const Vertex* data, size_t verticesCount, glm::vec3 color) : verticesCount(verticesCount), color(color)
{
	this->vao.bind();

	this->vbo.bind();
	this->vbo.setData(data, sizeof(Vertex) * verticesCount, GL_STATIC_DRAW);

	Program::setAttribute(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*) offsetof(Vertex, position));

	this->vao.unbind();
}

void SimpleConstantRenderer::update()
{
	ProgramManager::getInstance().use(ProgramManager::PROGRAM_SIMPLE_CONSTANT);

	Transform& transform = this->gameObject->getTransform();

	if (transform.isDirty())
	{
		ProgramManager::getInstance().getCurrentProgram().setModelMatrix(this->gameObject->getTransform().getModel());
		transform.clearDirty({ TransformDirtyBit::Position, TransformDirtyBit::Rotation, TransformDirtyBit::Scale });
	}

	ProgramManager::getInstance().getCurrentProgram().setUniform3f("color", this->color);

	this->vao.bind();
	RenderUtils::drawTriangles(0, this->verticesCount);
	this->vao.unbind();
}
void SimpleConstantRenderer::dispose()
{
	this->vbo.dispose();
	this->vao.dispose();
}