#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>

#include "../program.h"
#include "attenuation.h"
#include "phong.h"

struct PointLight
{
public:
	glm::vec3 position;
	
	Attenuation attenuation;
	Phong phong;

	PointLight();
	PointLight(const glm::vec3& position, const Attenuation& attenuation, const Phong& phong);

	void setUniforms(Program& program, std::string name);
};