#version 330 core

//VERTEX_DATA

//LIGHT_DEFINITIONS

in VertexData vertexData;

out vec4 outColor;

uniform sampler2D textureDiffuse;
uniform bool textureDiffuseValid;

uniform sampler2D textureSpecular;
uniform bool textureSpecularValid;

uniform sampler2D depthMap;

uniform sampler2D textureBump;
uniform bool textureBumpValid;

uniform vec3 viewPosition;
uniform vec3 color;

uniform bool useShadows;
uniform bool useBumpMap;

//PHONG_CALCULATIONS

void main()
{
	vec3 normal = normalize(vertexData.normal);

	if (textureBumpValid && useBumpMap)
	{
		vec3 bitangent = cross(normalize(vertexData.tangent), normal);

		mat3 TBN = mat3(vertexData.tangent, bitangent, normal);

		normal = texture(textureBump, vertexData.texCoords).rgb;
		normal = normalize(normal * 2.0 - 1.0);
		normal = normalize(TBN * normal);
	}

	vec3 viewDir = normalize(viewPosition - vertexData.worldPosition);
	vec3 diffuseMap = color;
	vec3 specularMap = vec3(1.0f);

	if (textureDiffuseValid)
	{
		diffuseMap *= vec3(texture(textureDiffuse, vertexData.texCoords));
	}
	if (textureSpecularValid)
	{
		specularMap *= vec3(texture(textureSpecular, vertexData.texCoords));
	}

	vec3 resultColor = vec3(0.0f, 0.0f, 0.0f);

	//vec3 dirLightComponent = calcDirLight(directionalLight, normal, viewDir, diffuseMap, specularMap, 256.0f);
	//resultColor += dirLightComponent;

	for (int i = 0; i < pointLightCount; i++)
	{
		vec3 pointLightComponent = calcPointLight(pointLights[i], normal, vertexData.worldPosition, viewDir, diffuseMap, specularMap, 32.0f);
		resultColor += pointLightComponent;
	}

	vec3 spotLightComponent = calcSpotLight(spotLight, normal, vertexData.worldPosition, viewDir, diffuseMap, specularMap, 32.0f);
	resultColor += spotLightComponent;

	vec3 lightDir = normalize(directionalLight.direction);
	
	float diff, spec;
	calcDiffSpec(lightDir, normal, viewDir, 256.0f, diff, spec);

	vec3 ambient = directionalLight.phong.ambient * diffuseMap;
	vec3 diffuse = directionalLight.phong.diffuse * diff;
	vec3 specular = directionalLight.phong.specular * spec;

	if (useShadows)
	{
		float shadow = calculateShadow(vertexData.worldPosLightSpace, normal, lightDir);
		resultColor += (ambient + (1.0f - shadow) * (diffuse + specular)) * diffuseMap;
	}

	outColor = vec4(resultColor, 1.0f);
}