#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>

#include "../program.h"
#include "phong.h"

struct DirectionalLight
{
public:
	glm::vec3 direction;
	Phong phong;

	DirectionalLight();
	DirectionalLight(const glm::vec3& direction, const Phong& phong);

	void setUniforms(Program& program, std::string name);
};