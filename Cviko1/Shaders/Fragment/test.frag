#version 330 core

out vec4 outColor;

in vec3 outPosition;

uniform vec3 color;

void main()
{
	outColor = vec4(outPosition, 1.0);
}