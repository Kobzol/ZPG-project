#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoords;
layout(location = 3) in vec3 tangent;

struct VertexData {
	vec3 worldPosition;
	vec3 normal;
	vec2 texCoords;
	vec4 worldPosLightSpace;
	mat3 TBN;
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

	vec3 bitangent = cross(normalize(tangent), vertexData.normal);

	vec3 T = normalize(vec3(modelMatrix * vec4(tangent,   0.0)));
	vec3 B = normalize(vec3(modelMatrix * vec4(bitangent, 0.0)));
	vec3 N = normalize(vec3(modelMatrix * vec4(normal,    0.0)));
	vertexData.TBN = mat3(T, B, N);

	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1.0f);
}