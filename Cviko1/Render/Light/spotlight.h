#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <cmath>

#include "../program.h"
#include "attenuation.h"
#include "phong.h"

struct SpotLight
{
public:
	glm::vec3 position;
	glm::vec3 direction;

	GLfloat cutOff;
	GLfloat outerCutOff;

	Attenuation attenuation;
	Phong phong;

	SpotLight();
	SpotLight(
		const glm::vec3& position, const glm::vec3& direction,
		GLfloat cutOff, GLfloat outerCutOff, const Attenuation& attenuation, const Phong& phong);

	void setUniforms(Program& program, std::string name);
};