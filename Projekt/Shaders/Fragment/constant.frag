#version 330 core

struct VertexData {
	vec3 worldPosition;
	vec3 normal;
	vec2 texCoords;
	vec4 worldPosLightSpace;
	mat3 TBN;
};

in VertexData vertexData;

out vec4 outColor;

uniform vec3 color;

void main()
{
	outColor = vec4(color, 1.0f);
}