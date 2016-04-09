#version 330 core

//VERTEX_DATA

in VertexData vertexData;

out vec4 outColor;

uniform sampler2D textureDiffuse;
uniform bool textureDiffuseValid;

uniform sampler2D textureSpecular;
uniform bool textureSpecularValid;

uniform sampler2D textureBump;
uniform bool textureBumpValid;

uniform vec3 viewPosition;
uniform vec3 color;

uniform bool useShadows;
uniform bool useBumpMap;

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

	vec3 resultColor = diffuseMap * color;

	outColor = vec4(resultColor, 1.0f);
}