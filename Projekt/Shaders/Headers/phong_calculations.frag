void calcAttenuation(float dist, Attenuation attenuationIn, out float attenuationOut);
void calcDiffSpec(vec3 lightDir, vec3 normal, vec3 viewDir, float shininess, out float diff, out float spec);
vec3 calcDirLight(DirLight light, vec3 normal, vec3 viewDir, vec3 diffuseMap, vec3 specularMap, float shininess);
vec3 calcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 diffuseMap, vec3 specularMap, float shininess);
vec3 calcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 diffuseMap, vec3 specularMap, float shininess);

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