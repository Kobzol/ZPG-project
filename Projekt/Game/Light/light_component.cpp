#include "light_component.h"

LightComponent::LightComponent(Light* light, std::string name) : light(light), name(name)
{
	
}

void LightComponent::update()
{
	ProgramManager::getInstance().use(ProgramManager::PROGRAM_MODEL);

	glm::vec3 position = this->gameObject->getTransform().getPosition();

	this->light->setUniforms(ProgramManager::getInstance().getCurrentProgram(), this->name, position);
}

void LightComponent::dispose()
{
	delete this->light;
}