#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

struct VertexData {
	vec4 worldPosition;
	vec3 outNormal;
};

out VertexData outVertex;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 normalMatrix

void main()
{
	outVertex.outNormal = normalMatrix * normal;
	outVertex.worldPosition = modelMatrix * vec4(position, 1.0f);

	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1.0f);
}