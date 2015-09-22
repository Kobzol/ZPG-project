#version 330 core

struct Material {
    float shininess;
}; 

struct Light {
    vec3 position;
	vec3 direction;
	float cutOff;
	float outerCutOff;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

	float constant;
	float linear;
	float quadratic;
};

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

out vec4 outColor;

uniform Material material;
uniform sampler2D materialDiffuse;
uniform sampler2D materialSpecular;
uniform Light light;
uniform vec3 viewPos;

void main()
{
	vec3 lightDir = normalize(light.position - FragPos);

	vec3 diffuseMap = vec3(texture(materialDiffuse, TexCoords));
	vec3 specularMap = vec3(texture(materialSpecular, TexCoords));

	// ambient;
	vec3 ambient = light.ambient * diffuseMap;

	// diffuse
	vec3 norm = normalize(Normal);
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = light.diffuse * diff * diffuseMap;

	// specular
	float specularStrength = 0.5f;
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
	vec3 specular = light.specular * (spec * specularMap);

	float lightDistance = length(light.position - FragPos);
	float attenuation = 1.0f /
						(light.constant + light.linear * lightDistance + light.quadratic * (lightDistance * lightDistance));

	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	float theta = dot(lightDir, normalize(-light.direction));
	float epsilon = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0f, 1.0f);

	diffuse *= intensity;
	specular *= intensity;

	vec3 color = ambient + diffuse + specular;

	outColor = vec4(color, 1.0f);
}