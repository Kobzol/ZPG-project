#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>

#include "../program.h"

struct Attenuation {
public:
	GLfloat constant;
	GLfloat linear;
	GLfloat quadratic;

	Attenuation();
	Attenuation(GLfloat constant, GLfloat linear, GLfloat quadratic);

	void setUniforms(Program& program, std::string name);
};