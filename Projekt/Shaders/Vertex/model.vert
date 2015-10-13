#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoords;

struct VertexData {
	vec4 worldPosition;
	vec3 outNormal;
	vec2 texCoords;
};

out VertexData outVertex;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

void main()
{
	outVertex.outNormal = transpose(inverse(mat3(Model))) * normal;
	outVertex.worldPosition = Model * vec4(position, 1.0f);
	outVertex.texCoords = texCoords;

	gl_Position = Projection * View * Model * vec4(position, 1.0f);
}