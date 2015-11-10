#include "simple_constant_renderer.h"

SimpleConstantRenderer::SimpleConstantRenderer(const VertexSimple* data, size_t verticesCount, glm::vec3 color) : color(color)
{
	this->geometryObject.setGeometry(data, sizeof(VertexSimple), verticesCount);
	this->geometryObject.setAttributePosition();
}

void SimpleConstantRenderer::update()
{
	Program& program = ProgramManager::getInstance().use(ProgramManager::PROGRAM_SIMPLE_CONSTANT);
	Context& context = Game::getInstance().getContext();

	program.setModelMatrix(this->gameObject->getTransform().getModel());
	program.setUniform3f("color", this->color);

	this->geometryObject.getVAO().bind();
	context.setStencilFunc(GL_ALWAYS, this->getGameObject()->getId(), 0xFF);

	RenderUtils::drawTriangles(0, this->geometryObject.getVertexCount());
	this->geometryObject.getVAO().unbind();
}
void SimpleConstantRenderer::dispose()
{
	this->geometryObject.dispose();
}