#version 330 core

layout (location = 0) in vec3 position;

out vec3 TexCoords;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

void main()
{
	mat4 viewNoTranslation = mat4(mat3(viewMatrix));
	vec4 pos = projectionMatrix * viewNoTranslation * vec4(position, 1.0);

    gl_Position = pos.xyww;	// z will always be 1.0f so that we can use depth test
	TexCoords = position;
}  