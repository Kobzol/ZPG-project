#include "directional_light.h"

DirectionalLight::DirectionalLight(const Phong& phong) : phong(phong)
{
	
}

void DirectionalLight::setUniforms(Program& program, std::string name, glm::vec3 position)
{
	program.setUniform3f(name + ".direction", position);
	this->phong.setUniforms(program, name + ".phong");
}