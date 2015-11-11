#version 330 core

in vec2 TexCoords;

out vec4 outColor;

uniform sampler2D tex;
uniform vec3 color;

void main()
{
	vec4 texColor = texture(tex, TexCoords) * vec4(color, 1.0f);
	outColor = texColor;
}