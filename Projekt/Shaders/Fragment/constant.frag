#version 330 core

//VERTEX_DATA

in VertexData vertexData;

out vec4 outColor;

uniform vec3 color;

void main()
{
	outColor = vec4(color, 1.0f);
}