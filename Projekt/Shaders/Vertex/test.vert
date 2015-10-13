#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

struct VertexData {
	vec4 worldPosition;
	vec3 outNormal;
};

out VertexData outVertex;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

void main()
{
	mat3 normalMat = transpose(inverse(mat3(Model)));
	outVertex.outNormal = normalMat * normal;
	outVertex.worldPosition = Model * vec4(position, 1.0f);

	gl_Position = Projection * View * Model * vec4(position, 1.0f);
}