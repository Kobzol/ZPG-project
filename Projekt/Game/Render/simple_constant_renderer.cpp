#include "simple_constant_renderer.h"

SimpleConstantRenderer::SimpleConstantRenderer(GeometryObject geometry, std::string shader, glm::vec3 color) : geometryObject(geometry), shader(shader), color(color)
{
	
}

void SimpleConstantRenderer::update()
{
	Program& program = ProgramManager::getInstance().use(this->shader);
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