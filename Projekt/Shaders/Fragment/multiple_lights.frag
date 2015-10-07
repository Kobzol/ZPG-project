#version 330 core

struct Material {
    float shininess;
};

struct Phong {
	vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct Attenuation {
	float constant;
	float linear;
	float quadratic;
};

struct PointLight {
    vec3 position;

	Attenuation attenuation;
    Phong phong;
};

struct DirLight {
    vec3 direction;
  
    Phong phong;
};

struct SpotLight {
	vec3 position;
    vec3 direction;
	float cutOff;
	float outerCutOff;

	Attenuation attenuation;
	Phong phong;
};

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

out vec4 outColor;

#define NR_POINT_LIGHTS 4  
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform DirLight dirLight;
uniform SpotLight spotLight;
uniform Material material;
uniform sampler2D materialDiffuse;
uniform sampler2D materialSpecular;
uniform vec3 viewPos;

void CalcDiffSpec(vec3 lightDir, vec3 normal, vec3 viewDir, out float diff, out float spec);
void CalcAttenuation(float dist, Attenuation attenuationIn, out float attenuationOut);
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir, vec3 diffuseMap, vec3 specularMap);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 diffuseMap, vec3 specularMap);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 diffuseMap, vec3 specularMap);

void main()
{
	vec3 normal = normalize(Normal);
	vec3 viewDir = normalize(viewPos - FragPos);

	vec3 diffuseMap = vec3(texture(materialDiffuse, TexCoords));
	vec3 specularMap = vec3(texture(materialSpecular, TexCoords));

	// directional lights
	vec3 color = CalcDirLight(dirLight, normal, viewDir, diffuseMap, specularMap);

	// points lights
	for (int i = 0; i < NR_POINT_LIGHTS; i++)
	{
		color += CalcPointLight(pointLights[i], normal, FragPos, viewDir, diffuseMap, specularMap);
	}

	// spotlights
	color += CalcSpotLight(spotLight, normal, FragPos, viewDir, diffuseMap, specularMap);

	outColor = vec4(color, 1.0f);
}

void CalcDiffSpec(vec3 lightDir, vec3 normal, vec3 viewDir, out float diff, out float spec)
{
	diff = max(dot(normal, lightDir), 0.0f);

	// specular shading
	vec3 reflectDir = reflect(-lightDir, normal);
	spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
}

void CalcAttenuation(float dist, Attenuation attenuationIn, out float attenuationOut)
{
	attenuationOut = 1.0f / (attenuationIn.constant + attenuationIn.linear * dist + 
  			     attenuationIn.quadratic * (dist * dist));
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir, vec3 diffuseMap, vec3 specularMap)
{
	vec3 lightDir = normalize(-light.direction);
	
	float diff, spec;
	CalcDiffSpec(lightDir, normal, viewDir, diff, spec);

	vec3 ambient = light.phong.ambient * diffuseMap;
	vec3 diffuse = light.phong.diffuse * diff * diffuseMap;
	vec3 specular = light.phong.specular * spec * specularMap;

	return (ambient + diffuse + specular);
}

// Calculates the color when using a point light.
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 diffuseMap, vec3 specularMap)
{
    vec3 lightDir = normalize(light.position - fragPos);

	float diff, spec;
	CalcDiffSpec(lightDir, normal, viewDir, diff, spec);

    // attenuation
    float dist    = length(light.position - fragPos);
    float attenuation;
	CalcAttenuation(dist, light.attenuation, attenuation);

    // combine results
    vec3 ambient  = light.phong.ambient  * diffuseMap;
    vec3 diffuse  = light.phong.diffuse  * diff * diffuseMap;
    vec3 specular = light.phong.specular * spec * specularMap;

    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;

    return (ambient + diffuse + specular);
}

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 diffuseMap, vec3 specularMap)
{
	vec3 lightDir = normalize(light.position - fragPos);

	float diff, spec;
	CalcDiffSpec(lightDir, normal, viewDir, diff, spec);

	float theta = dot(lightDir, normalize(-light.direction));
	float epsilon = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0f, 1.0f);

	float dist = length(light.position - fragPos);
	float attenuation;
	CalcAttenuation(dist, light.attenuation, attenuation);

	vec3 ambient = light.phong.ambient * diffuseMap;
	vec3 diffuse = light.phong.diffuse * diff * diffuseMap;
	vec3 specular = light.phong.specular * spec * specularMap;

	ambient *= attenuation * intensity;
	diffuse *= attenuation * intensity;
	specular *= attenuation * intensity;

	return (ambient + diffuse + specular);
}