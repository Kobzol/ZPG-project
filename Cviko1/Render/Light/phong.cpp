#include "phong.h"

Phong::Phong()
{

}

Phong::Phong(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular) :
	ambient(ambient), diffuse(diffuse), specular(specular)
{

}

void Phong::setUniforms(Program& program, std::string name)
{
	program.setUniform3f(name + ".ambient", this->ambient);
	program.setUniform3f(name + ".diffuse", this->diffuse);
	program.setUniform3f(name + ".specular", this->specular);
}