#version 330 core

in vec3 Normal;
in vec3 FragPos;

out vec4 outColor;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{
	// ambient
	float ambientStrength = 0.1f;
    vec3 ambient = ambientStrength * lightColor;

	// diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = lightColor * diff;

	// specular
	float specularStrength = 0.5f;
	vec3 viewDir = normalize(viewPos - FragPos);

	// Phong
	/*vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 32.0f);*/
	
	// Blinn-Phong
	vec3 halfwayDir = normalize(lightDir + viewDir);
	float spec = pow(max(dot(normal, halfwayDir), 0.0f), 64.0f);

	vec3 specular = lightColor * spec;

	vec3 color = ambient + diffuse + specular;

	outColor = vec4(color * objectColor, 1.0f);
}