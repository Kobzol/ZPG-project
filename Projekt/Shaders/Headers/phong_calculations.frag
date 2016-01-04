void calcAttenuation(float dist, Attenuation attenuationIn, out float attenuationOut);
void calcDiffSpec(vec3 lightDir, vec3 normal, vec3 viewDir, float shininess, out float diff, out float spec);
vec3 calcDirLight(DirLight light, vec3 normal, vec3 viewDir, vec3 diffuseMap, vec3 specularMap, float shininess);
vec3 calcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 diffuseMap, vec3 specularMap, float shininess);
vec3 calcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 diffuseMap, vec3 specularMap, float shininess);
float calculateShadow(vec4 lightSpacePosition, vec3 normal, vec3 lightDir);

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
	vec3 lightDir = normalize(light.direction);
	
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
float calculateShadow(vec4 lightSpacePosition, vec3 normal, vec3 lightDir)
{
	vec3 projCoords = lightSpacePosition.xyz / lightSpacePosition.w;
	projCoords = projCoords * 0.5f + 0.5f;	// project to NDC [0,1]

	if (projCoords.z > 1.0f)
    {
		return 0.0f;
	}

	float shadow = 0.0;
	vec2 texelSize = 1.0 / textureSize(depthMap, 0);
	float currentDepth = projCoords.z;
	float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);

	for(int x = -1; x <= 1; ++x)
	{
		for(int y = -1; y <= 1; ++y)
		{
			float pcfDepth = texture(depthMap, projCoords.xy + vec2(x, y) * texelSize).r; 
			shadow += currentDepth - bias > pcfDepth ? 1.0f : 0.0f;    
		}    
	}
	shadow /= 9.0;

	return shadow;
}