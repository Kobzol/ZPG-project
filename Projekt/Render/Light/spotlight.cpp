#include "spotlight.h"

SpotLight::SpotLight()
{

}

SpotLight::SpotLight(
	const glm::vec3& position, const glm::vec3& direction,
	GLfloat cutOff, GLfloat outerCutOff, const Attenuation& attenuation, const Phong& phong) :
	position(position), direction(direction), cutOff(cutOff), outerCutOff(outerCutOff),
	attenuation(attenuation), phong(phong)
{

}

void SpotLight::setUniforms(Program& program, std::string name)
{
	program.setUniform3f(name + ".position", this->position);
	program.setUniform3f(name + ".direction", this->direction);
	program.setUniform1f(name + ".cutOff", std::cos(glm::radians(this->cutOff)));
	program.setUniform1f(name + ".outerCutOff", std::cos(glm::radians(this->outerCutOff)));
	
	this->attenuation.setUniforms(program, name + ".attenuation");
	this->phong.setUniforms(program, name + ".phong");
}