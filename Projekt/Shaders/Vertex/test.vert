#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

out vec4 worldPosition;
out vec3 outNormal;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

void main()
{
	mat3 normalMat = transpose(inverse(mat3(Model)));
	outNormal = normalMat * normal;
	worldPosition = Model * vec4(position, 1.0f);

	gl_Position = Projection * View * Model * vec4(position, 1.0f);
}