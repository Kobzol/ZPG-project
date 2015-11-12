#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoords;

struct VertexData {
	vec3 worldPosition;
	vec3 normal;
	vec2 texCoords;
	vec4 worldPosLightSpace;
};

out VertexData vertexData;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 lightSpaceMatrix;
uniform mat3 normalMatrix;

void main()
{
	vertexData.normal = normalMatrix * normal;
	vertexData.worldPosition = vec3(modelMatrix * vec4(position, 1.0f));
	vertexData.texCoords = texCoords;
	vertexData.worldPosLightSpace = lightSpaceMatrix * vec4(vertexData.worldPosition, 1.0f);

	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1.0f);
}