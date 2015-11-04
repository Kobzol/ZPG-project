#version 330 core

struct VertexData {
	vec3 worldPosition;
	vec3 normal;
	vec2 texCoords;
};
struct Attenuation {
	float constant;
	float linear;
	float quadratic;
};
struct Phong {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
struct DirLight {
	vec3 direction;
	Phong phong;
};
struct PointLight {
    vec3 position;

	Attenuation attenuation;
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

in VertexData vertexData;

out vec4 outColor;

uniform sampler2D textureDiffuse1;
uniform sampler2D textureSpecular1;

uniform DirLight directionalLight;

#define MAX_POINT_LIGHTS 3
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform int pointLightCount;

uniform SpotLight spotLight;

uniform vec3 viewPosition;

void calcAttenuation(float dist, Attenuation attenuationIn, out float attenuationOut);
void calcDiffSpec(vec3 lightDir, vec3 normal, vec3 viewDir, float shininess, out float diff, out float spec);
vec3 calcDirLight(DirLight light, vec3 normal, vec3 viewDir, vec3 diffuseMap, vec3 specularMap, float shininess);
vec3 calcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 diffuseMap, vec3 specularMap, float shininess);
vec3 calcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 diffuseMap, vec3 specularMap, float shininess);

void main()
{
	vec3 normal = normalize(vertexData.normal);
	vec3 viewDir = normalize(viewPosition - vertexData.worldPosition);
	vec3 diffuseMap = vec3(0.2f, 0.7f, 1.0f);//vec3(texture(textureDiffuse1, vertexData.texCoords));
	vec3 specularMap = vec3(1.0f);//vec3(texture(textureSpecular1, vertexData.texCoords));

	vec3 resultColor = vec3(0.0f, 0.0f, 0.0f);

	vec3 dirLightComponent = calcDirLight(directionalLight, normal, viewDir, diffuseMap, specularMap, 256.0f);
	resultColor += dirLightComponent;

	for (int i = 0; i < pointLightCount; i++)
	{
		vec3 pointLightComponent = calcPointLight(pointLights[i], normal, vertexData.worldPosition, viewDir, diffuseMap, specularMap, 32.0f);
		resultColor += pointLightComponent;
	}

	vec3 spotLightComponent = calcSpotLight(spotLight, normal, vertexData.worldPosition, viewDir, diffuseMap, specularMap, 32.0f);
	resultColor += spotLightComponent;

	outColor = vec4(resultColor, 1.0f);
}

void calcAttenuation(float dist, Attenuation attenuationIn, out float attenuationOut)
{
	attenuationOut = 1.0f / (attenuationIn.constant + attenuationIn.linear * dist + 
  			     attenuationIn.quadratic * (dist * dist));
}
void calcDiffSpec(vec3 lightDir, vec3 normal, vec3 viewDir, float shininess, out float diff, out float spec)
{
	// diffuse component
	diff = max(dot(normal, lightDir), 0.0f);

	// specular component
	vec3 halfwayDir = normalize(lightDir + viewDir);
	spec = pow(max(dot(normal, halfwayDir), 0.0f), shininess);
}
vec3 calcDirLight(DirLight light, vec3 normal, vec3 viewDir, vec3 diffuseMap, vec3 specularMap, float shininess)
{
	vec3 lightDir = normalize(-light.direction);
	
	float diff, spec;
	calcDiffSpec(lightDir, normal, viewDir, shininess, diff, spec);

	vec3 ambient = light.phong.ambient * diffuseMap;
	vec3 diffuse = light.phong.diffuse * diff * diffuseMap;
	vec3 specular = light.phong.specular * spec * specularMap;

	return (ambient + diffuse + specular);
}
vec3 calcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 diffuseMap, vec3 specularMap, float shininess)
{
    vec3 lightDir = normalize(light.position - fragPos);

	float diff, spec;
	calcDiffSpec(lightDir, normal, viewDir, shininess, diff, spec);

    // attenuation
    float dist    = length(light.position - fragPos);
    float attenuation;
	calcAttenuation(dist, light.attenuation, attenuation);

    // combine results
    vec3 ambient  = light.phong.ambient  * diffuseMap;
    vec3 diffuse  = light.phong.diffuse  * diff * diffuseMap;
    vec3 specular = light.phong.specular * spec * specularMap;

    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;

    return (ambient + diffuse + specular);
}
vec3 calcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 diffuseMap, vec3 specularMap, float shininess)
{
	vec3 lightDir = normalize(light.position - fragPos);

	float diff, spec;
	calcDiffSpec(lightDir, normal, viewDir, shininess, diff, spec);

	float theta = dot(lightDir, normalize(-light.direction));
	float epsilon = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0f, 1.0f);

	float dist = length(light.position - fragPos);
	float attenuation;
	calcAttenuation(dist, light.attenuation, attenuation);

	vec3 ambient = light.phong.ambient * diffuseMap;
	vec3 diffuse = light.phong.diffuse * diff * diffuseMap;
	vec3 specular = light.phong.specular * spec * specularMap;

	ambient *= attenuation * intensity;
	diffuse *= attenuation * intensity;
	specular *= attenuation * intensity;

	return (ambient + diffuse + specular);
}