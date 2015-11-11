#include "sprite_draw_module.h"

SpriteDrawModule::SpriteDrawModule(std::string textureId) : textureId(textureId)
{
	this->spriteGeometry.setGeometry(VERTICES_SPRITE, 4 * sizeof(GLfloat), 6);
	this->spriteGeometry.setAttributePositionTexture2D();
}

void SpriteDrawModule::update(RenderComponent* component)
{
	Texture& texture = TextureManager::getInstance().get(this->textureId);
	texture.bind(0);

	Context& context = Game::getInstance().getContext();

	Program& program = ProgramManager::getInstance().getCurrentProgram();
	program.setProjectionMatrix(glm::ortho(0.0f, (float)context.getWindowWidth(), (float)context.getWindowHeight(), 0.0f, -1.0f, 1.0f));

	Transform& transform = component->getGameObject()->getTransform();
	glm::vec3 position = transform.getPosition();
	glm::vec3 scale = transform.getScale();

	glm::mat4 model;
	// translate
	model = glm::translate(model, glm::vec3(position.x, position.y, 0.0f) + glm::vec3(-scale.x * 0.5f, -scale.y * 0.5f, 0.0f));

	// rotate
	model = glm::translate(model, glm::vec3(scale.x * 0.5f, scale.y * 0.5f, 0.0f));
	model *= glm::mat4_cast(transform.getRotation());
	model = glm::translate(model, glm::vec3(-scale.x * 0.5f, -scale.y * 0.5f, 0.0f));

	// scale
	model = glm::scale(model, scale);

	program.setModelMatrix(model, false);

	this->spriteGeometry.getVAO().bind();
	RenderUtils::drawTriangles(0, 6);
	this->spriteGeometry.getVAO().unbind();
}
void SpriteDrawModule::dispose()
{
	this->spriteGeometry.dispose();
}