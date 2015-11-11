#version 330 core

in vec3 TexCoords;

out vec4 outColor;

uniform samplerCube skybox;
uniform vec3 color;

void main()
{    
    outColor = texture(skybox, TexCoords) * vec4(color, 1.0f);
}