#include "point_light.h"

PointLight::PointLight()
{

}

PointLight::PointLight(const glm::vec3& position, const Attenuation& attenuation, const Phong& phong) :
position(position), attenuation(attenuation), phong(phong)
{
	
}

void PointLight::setUniforms(Program& program, std::string name)
{
	program.setUniform3f(name + ".position", this->position);
	
	this->attenuation.setUniforms(program, name + ".attenuation");
	this->phong.setUniforms(program, name + ".phong");
}