#version 330 core

in vec3 Normal;
in vec3 FragPos;
in vec3 Color;

out vec4 outColor;

void main()
{
	outColor = vec4(Color, 1.0f);
}