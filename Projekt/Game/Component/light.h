#pragma once

#include <string>

#include "icomponent.h"
#include "../../Content/program_manager.h"

template <typename T>
class Light : public IComponent
{
public:
	Light(T& t, std::string name) : t(t), name(name)
	{
		
	}

	void update()
	{
		this->t.setUniforms(ProgramManager::getInstance().getCurrentProgram(), this->name);
	}

private:
	T t;
	std::string name;
};