#include "directional_light.h"

DirectionalLight::DirectionalLight()
{

}

DirectionalLight::DirectionalLight(const glm::vec3& direction, const Phong& phong) : direction(direction), phong(phong)
{
	
}

void DirectionalLight::setUniforms(Program& program, std::string name)
{
	program.setUniform3f(name + ".direction", this->direction);
	this->phong.setUniforms(program, name + ".phong");
}