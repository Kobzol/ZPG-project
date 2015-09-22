#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>

#include "../program.h"

struct Phong {
public:
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	Phong();
	Phong(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular);

	void setUniforms(Program& program, std::string name);
};