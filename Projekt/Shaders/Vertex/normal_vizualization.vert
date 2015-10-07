#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;

out VertexParams {
    vec3 normal;
} params_out;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
	vec2 tmp = texCoords;

    gl_Position = projection * view * model * vec4(position, 1.0f); 
    mat3 normalMatrix = mat3(transpose(inverse(view * model)));
    params_out.normal = normalize(vec3(projection * vec4(normalMatrix * normal, 1.0)));
}