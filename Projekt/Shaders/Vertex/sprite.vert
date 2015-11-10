#version 330 core

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 texCoords;

out vec2 TexCoords;

uniform mat4 modelMatrix;
uniform mat4 projectionMatrix;

void main()
{
	TexCoords = texCoords;
	gl_Position = projectionMatrix * modelMatrix * vec4(position, 0.0f, 1.0f);
}