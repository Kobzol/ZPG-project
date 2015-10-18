#version 330 core
in vec2 TexCoords;

out vec4 color;

uniform sampler2D screenTexture;

void main()
{ 
    vec4 texColor = texture(screenTexture, TexCoords);

	color = vec4(texColor);
}