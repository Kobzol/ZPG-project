#version 330 core

in vec2 TexCoords;

out vec4 outColor;

uniform sampler2D depthMap;

void main()
{
    float depthValue = texture(depthMap, TexCoords).r;
	outColor = vec4(vec3(depthValue), 1.0f);
}