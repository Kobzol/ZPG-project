#include "point_light.h"

PointLight::PointLight(const Attenuation& attenuation, const Phong& phong) : attenuation(attenuation), phong(phong)
{
	
}

void PointLight::setUniforms(Program& program, std::string name, glm::vec3 position)
{
	program.setUniform3f(name + ".position", position);
	
	this->attenuation.setUniforms(program, name + ".attenuation");
	this->phong.setUniforms(program, name + ".phong");
}