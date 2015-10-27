#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <cmath>

#include "light.h"
#include "../../Render/Light/attenuation.h"
#include "../../Render/Light/phong.h"
#include "../../Render/program.h"

struct SpotLight : Light
{
public:
	glm::vec3 direction;

	GLfloat cutOff;
	GLfloat outerCutOff;

	Attenuation attenuation;
	Phong phong;

	SpotLight(const glm::vec3& direction, GLfloat cutOff, GLfloat outerCutOff, const Attenuation& attenuation, const Phong& phong);

	void setUniforms(Program& program, std::string name, glm::vec3 position) override;
};