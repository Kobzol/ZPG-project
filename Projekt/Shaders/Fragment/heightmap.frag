#version 330 core

struct VertexData {
	vec3 worldPosition;
	vec2 texCoords;
};

in VertexData vertexData;

uniform sampler2D heightMapTexture;

out vec4 outColor;

void main()
{
	outColor = vec4(vec3(texture(heightMapTexture, vertexData.texCoords)), 1.0f);
}