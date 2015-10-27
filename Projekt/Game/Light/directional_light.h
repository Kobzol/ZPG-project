#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>

#include "light.h"
#include "../../Render/program.h"
#include "../../Render/Light/phong.h"

struct DirectionalLight : Light
{
public:
	glm::vec3 direction;
	Phong phong;

	DirectionalLight(const glm::vec3& direction, const Phong& phong);

	void setUniforms(Program& program, std::string name, glm::vec3 position) override;
};