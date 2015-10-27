#pragma once

#include <string>

#include "../../Render/program.h"

class Light
{
public:
	virtual void setUniforms(Program& program, std::string name, glm::vec3 position) = 0;
};