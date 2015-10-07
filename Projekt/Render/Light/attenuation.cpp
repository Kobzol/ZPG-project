#include "attenuation.h"

Attenuation::Attenuation()
{

}

Attenuation::Attenuation(GLfloat constant, GLfloat linear, GLfloat quadratic)
	: constant(constant), linear(linear), quadratic(quadratic)
{

}

void Attenuation::setUniforms(Program& program, std::string name)
{
	program.setUniform1f(name + ".constant", this->constant);
	program.setUniform1f(name + ".linear", this->linear);
	program.setUniform1f(name + ".quadratic", this->quadratic);
}