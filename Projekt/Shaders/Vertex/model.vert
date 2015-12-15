#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoords;
layout(location = 3) in vec3 tangent;

//VERTEX_DATA

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
	vertexData.tangent = tangent;

	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1.0f);
}