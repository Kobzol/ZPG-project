#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;

// Declare an interface block; see 'Advanced GLSL' for what these are.
out VertexParams {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
} params_out;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0f);
    params_out.FragPos = vec3(model * vec4(position, 1.0));
    params_out.TexCoords = texCoords;
    
    mat3 normalMatrix = transpose(inverse(mat3(model)));
    params_out.Normal = normalMatrix * normal;
}