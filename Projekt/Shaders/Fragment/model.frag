#version 330 core

struct VertexData {
	vec3 worldPosition;
	vec3 normal;
	vec2 texCoords;
	vec4 worldPosLightSpace;
};

#LIGHT_DEFINITIONS

in VertexData vertexData;

out vec4 outColor;

uniform sampler2D textureDiffuse1;
uniform sampler2D textureSpecular1;
uniform sampler2D depthMap;

uniform vec3 viewPosition;
uniform vec3 color;

#PHONG_CALCULATIONS

float calculateShadow(vec4 lightSpacePosition)
{
	vec3 projCoords = lightSpacePosition.xyz / lightSpacePosition.w;
	projCoords = projCoords * 0.5f + 0.5f;	// project to NDC [0,1]
	float lightDepth = texture(depthMap, projCoords.xy).r;
	float currentDepth = projCoords.z;

	return (currentDepth > lightDepth ? 1.0f : 0.0f);
}

void main()
{
	vec3 normal = normalize(vertexData.normal);
	vec3 viewDir = normalize(viewPosition - vertexData.worldPosition);
	vec3 diffuseMap = color;//vec3(texture(textureDiffuse1, vertexData.texCoords));
	vec3 specularMap = vec3(1.0f);//vec3(texture(textureSpecular1, vertexData.texCoords));

	vec3 resultColor = vec3(0.0f, 0.0f, 0.0f);

	/*vec3 dirLightComponent = calcDirLight(directionalLight, normal, viewDir, diffuseMap, specularMap, 256.0f);
	resultColor += dirLightComponent;

	for (int i = 0; i < pointLightCount; i++)
	{
		vec3 pointLightComponent = calcPointLight(pointLights[i], normal, vertexData.worldPosition, viewDir, diffuseMap, specularMap, 32.0f);
		resultColor += pointLightComponent;
	}

	vec3 spotLightComponent = calcSpotLight(spotLight, normal, vertexData.worldPosition, viewDir, diffuseMap, specularMap, 32.0f);
	resultColor += spotLightComponent;*/

	vec3 lightDir = normalize(directionalLight.direction - vertexData.worldPosition);
	
	float diff, spec;
	calcDiffSpec(lightDir, normal, viewDir, 32.0f, diff, spec);

	vec3 ambient = directionalLight.phong.ambient * diffuseMap;
	vec3 diffuse = directionalLight.phong.diffuse * diff;
	vec3 specular = directionalLight.phong.specular * spec;

	float shadow = calculateShadow(vertexData.worldPosLightSpace);
    vec3 lighting = (ambient + (1.0f - shadow) * (diffuse + specular)) * diffuseMap;

	outColor = vec4(lighting, 1.0f);
}