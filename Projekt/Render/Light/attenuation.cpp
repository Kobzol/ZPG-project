#include "attenuation.h"

const Attenuation Attenuation::ATT_DISTANCE_SHORT = Attenuation(1.0f, 0.7f, 1.8f);
const Attenuation Attenuation::ATT_DISTANCE_LONG = Attenuation(1.0f, 0.007f, 0.0002f);

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