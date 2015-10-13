#version 330 core

in vec4 worldPosition;
in vec3 outNormal;

out vec4 outColor;

uniform vec3 color;

void main()
{
	vec3 light = vec3(normalize(vec4(10.0f, 10.0f, 10.0f, 1.0f) - worldPosition));
	float dotLight = max(dot(light, outNormal), 0.0f);
	
	vec3 diffColor = dotLight * color;
	vec3 ambientColor = vec3(0.1f, 0.1f, 0.1f);

	vec3 resultColor = diffColor + ambientColor;

	outColor = vec4(resultColor, 1.0f);
}