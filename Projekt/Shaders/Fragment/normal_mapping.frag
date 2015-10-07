#version 330 core

out vec4 outColor;

in VertexParams {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
} params_in;

uniform sampler2D diffuseMap;
uniform sampler2D normalMap;  

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform bool normalMapping;

void main()
{           
    vec3 normal = normalize(params_in.Normal);

    if(normalMapping)
    {
        // Obtain normal from normal map in range [0,1]
        normal = texture(normalMap, params_in.TexCoords).rgb;
        // Transform normal vector to range [-1,1]
        normal = normalize(normal * 2.0f - 1.0f);   
    }
     // Get diffuse color
    vec3 color = texture(diffuseMap, params_in.TexCoords).rgb;
    // Ambient
    vec3 ambient = 0.1f * color;
    // Diffuse
    vec3 lightDir = normalize(lightPos - params_in.FragPos);
    float diff = max(dot(lightDir, normal), 0.0f);
    vec3 diffuse = diff * color;
    // Specular
    vec3 viewDir = normalize(viewPos - params_in.FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    float spec = pow(max(dot(normal, halfwayDir), 0.0f), 32.0f);
    vec3 specular = vec3(0.2f) * spec;
    
    outColor = vec4(ambient + diffuse + specular, 1.0f);
}