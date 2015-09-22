#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;

out VertexParams {
	vec3 FragPos;
	vec3 Normal;
	vec2 TexCoords;
	vec4 FragPosLightSpace;
} params_out;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 lightSpaceMatrix;

void main()
{
	gl_Position = projection * view * model * vec4(position, 1.0f);

    params_out.FragPos = vec3(model * vec4(position, 1.0));
    params_out.Normal = transpose(inverse(mat3(model))) * normal;
    params_out.TexCoords = texCoords;
    params_out.FragPosLightSpace = lightSpaceMatrix * vec4(params_out.FragPos, 1.0);
}  