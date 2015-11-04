#include "light_component.h"

LightComponent::LightComponent(Light* light, std::string name, int index) : light(light), name(name)
{
	if (index != -1)
	{
		this->name = name + "[" + std::to_string(index) + "]";
	}
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