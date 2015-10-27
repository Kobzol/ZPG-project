#pragma once

#include <string>

#include "icomponent.h"
#include "../../Content/program_manager.h"

template <typename T>
class Light : public IComponent
{
public:
	Light(T& light, std::string name) : light(light), name(name)
	{
		
	}

	void update()
	{
		this->light.position = this->gameObject->getTransform().getPosition();
		this->light.setUniforms(ProgramManager::getInstance().getCurrentProgram(), this->name);
	}

private:
	T light;
	std::string name;
};