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
		vec3 tangent = normalize(vertexData.tangent - dot(vertexData.tangent, normal) * normal);
		vec3 bitangent = cross(tangent, normal);
		mat3 TBN = mat3(tangent, bitangent, normal);

		normal = texture(textureBump, vertexData.texCoords).rgb;
		normal = normalize(normal * 2.0f - 1.0f);
		normal = normalize(TBN * normal);
	}

	vec3 viewDir = normalize(viewPosition - vertexData.worldPosition);
	vec3 diffuseMap = color;
	vec3 specularMap = vec3(1.0f, 1.0f, 1.0f);

	if (textureDiffuseValid)
	{
		diffuseMap *= vec3(texture(textureDiffuse, vertexData.texCoords));
	}
	if (textureSpecularValid)
	{
		specularMap *= vec3(texture(textureSpecular, vertexData.texCoords));
	}

	vec3 resultColor = vec3(0.0f, 0.0f, 0.0f);

	for (int i = 0; i < pointLightCount; i++)
	{
		vec3 pointLightComponent = calcPointLight(pointLights[i], normal, vertexData.worldPosition, viewDir, diffuseMap, specularMap, 32.0f);
		resultColor += pointLightComponent;
	}

	for (int i = 0; i < spotLightCount; i++)
	{
		vec3 spotLightComponent = calcSpotLight(spotLights[i], normal, vertexData.worldPosition, viewDir, diffuseMap, specularMap, 32.0f);
		resultColor += spotLightComponent;
	}

	if (useShadows)
	{
		vec3 lightDir = normalize(directionalLight.direction);
		float diff, spec;
		calcDiffSpec(lightDir, normal, viewDir, 256.0f, diff, spec);

		vec3 ambient = directionalLight.phong.ambient * diffuseMap;
		vec3 diffuse = directionalLight.phong.diffuse * diff;
		vec3 specular = directionalLight.phong.specular * spec;

		float shadow = calculateShadow(vertexData.worldPosLightSpace, normal, lightDir);
		resultColor += (ambient + (1.0f - shadow) * (diffuse + specular)) * diffuseMap;
	}
	else resultColor += calcDirLight(directionalLight, normal, viewDir, diffuseMap, specularMap, 256.0f);

	outColor = vec4(resultColor, 1.0f);
}