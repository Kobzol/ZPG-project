#version 330 core

in vec3 Normal;
in vec3 Position;

out vec4 outColor;

uniform vec3 cameraPos;
uniform samplerCube skybox;

void main()
{
	vec3 I = normalize(Position - cameraPos);

	// refraction
	float ratio = 1.0f / 1.52f;
	vec3 R = refract(I, normalize(Normal), ratio);

	// reflection
	//vec3 R = reflect(I, normalize(Normal));

	outColor = texture(skybox, R);
}