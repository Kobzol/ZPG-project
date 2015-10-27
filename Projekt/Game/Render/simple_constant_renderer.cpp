#include "simple_constant_renderer.h"

SimpleConstantRenderer::SimpleConstantRenderer(const VertexSimple* data, size_t verticesCount, glm::vec3 color) : verticesCount(verticesCount), color(color)
{
	this->vao.bind();

	this->vbo.bind();
	this->vbo.setData(data, sizeof(VertexSimple) * verticesCount, GL_STATIC_DRAW);

	Program::setAttribute(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexSimple), 0);

	this->vao.unbind();
}

void SimpleConstantRenderer::update()
{
	Program& program = ProgramManager::getInstance().use(ProgramManager::PROGRAM_SIMPLE_CONSTANT);
	
	program.setModelMatrix(this->gameObject->getTransform().getModel());
	program.setUniform3f("color", this->color);

	this->vao.bind();
	RenderUtils::drawTriangles(0, this->verticesCount);
	this->vao.unbind();
}
void SimpleConstantRenderer::dispose()
{
	this->vbo.dispose();
	this->vao.dispose();
}