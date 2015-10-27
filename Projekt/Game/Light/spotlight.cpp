#include "spotlight.h"

SpotLight::SpotLight(const glm::vec3& direction,
	GLfloat cutOff, GLfloat outerCutOff, const Attenuation& attenuation, const Phong& phong) :
	direction(direction), cutOff(cutOff), outerCutOff(outerCutOff),
	attenuation(attenuation), phong(phong)
{

}

void SpotLight::setUniforms(Program& program, std::string name, glm::vec3 position)
{
	program.setUniform3f(name + ".position", position);
	program.setUniform3f(name + ".direction", this->direction);
	program.setUniform1f(name + ".cutOff", std::cos(glm::radians(this->cutOff)));
	program.setUniform1f(name + ".outerCutOff", std::cos(glm::radians(this->outerCutOff)));
	
	this->attenuation.setUniforms(program, name + ".attenuation");
	this->phong.setUniforms(program, name + ".phong");
}