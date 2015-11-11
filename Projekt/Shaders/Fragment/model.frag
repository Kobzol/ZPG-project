#version 330 core

struct VertexData {
	vec3 worldPosition;
	vec3 normal;
	vec2 texCoords;
};

#LIGHT_DEFINITIONS

in VertexData vertexData;

out vec4 outColor;

uniform sampler2D textureDiffuse1;
uniform sampler2D textureSpecular1;

uniform vec3 viewPosition;
uniform vec3 color;

#PHONG_CALCULATIONS

void main()
{
	vec3 normal = normalize(vertexData.normal);
	vec3 viewDir = normalize(viewPosition - vertexData.worldPosition);
	vec3 diffuseMap = color;//vec3(texture(textureDiffuse1, vertexData.texCoords));
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