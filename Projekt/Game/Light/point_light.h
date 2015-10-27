#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>

#include "light.h"
#include "../../Render/Light/attenuation.h"
#include "../../Render/Light/phong.h"
#include "../../Render/program.h"

struct PointLight : Light
{
public:
	Attenuation attenuation;
	Phong phong;

	PointLight(const Attenuation& attenuation, const Phong& phong);

	void setUniforms(Program& program, std::string name, glm::vec3 position) override;
};