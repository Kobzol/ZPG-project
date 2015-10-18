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

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat3 normalMatrix;

void main()
{
	outVertex.outNormal = normalMatrix * normal;
	outVertex.worldPosition = modelMatrix * vec4(position, 1.0f);
	outVertex.texCoords = texCoords;

	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1.0f);
}