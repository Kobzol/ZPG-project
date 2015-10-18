#version 330 core

struct VertexData {
	vec3 worldPosition;
	vec3 normal;
	vec2 texCoords;
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

in VertexData vertexData;

out vec4 outColor;

uniform sampler2D textureDiffuse1;
uniform sampler2D textureSpecular1;

uniform DirLight directionalLight;

uniform vec3 viewPosition;

void calcDiffSpec(vec3 lightDir, vec3 normal, vec3 viewDir, out float diff, out float spec);
vec3 calcDirLight(DirLight light, vec3 normal, vec3 viewDir, vec3 diffuseMap, vec3 specularMap);

void main()
{
	vec3 normal = normalize(vertexData.normal);
	vec3 viewDir = normalize(viewPosition - vertexData.worldPosition);
	vec3 diffuseMap = vec3(texture(textureDiffuse1, vertexData.texCoords));
	vec3 specularMap = vec3(texture(textureSpecular1, vertexData.texCoords));

	vec3 dirLight = calcDirLight(directionalLight, normal, viewDir, diffuseMap, specularMap);

	outColor = vec4(dirLight, 1.0f);


	/*vec4 lightPosition = vec4(-10.0f, 10.0f, 10.0f, 1.0f);
	vec3 ambient = vec3(0.1f, 0.1f, 0.1f);

	vec3 lightDir = normalize(-directionalLight.direction);
	float dotLight = max(dot(lightDir, normalize(outVertex.outNormal)), 0.0f);
	
	vec3 color = vec3(texture(texture_diffuse, outVertex.texCoords));

	vec3 diffColor = dotLight * color;
	vec3 ambientColor = ambient;

	outColor = vec4(diffColor + ambientColor, 1.0f);*/
}

void calcDiffSpec(vec3 lightDir, vec3 normal, vec3 viewDir, out float diff, out float spec)
{
	diff = max(dot(normal, lightDir), 0.0f);

	// specular shading
	vec3 reflectDir = reflect(-lightDir, normal);
	spec = pow(max(dot(viewDir, reflectDir), 0.0f), 32.0f);	// TODO set material shininess
}

vec3 calcDirLight(DirLight light, vec3 normal, vec3 viewDir, vec3 diffuseMap, vec3 specularMap)
{
	vec3 lightDir = normalize(-light.direction);
	
	float diff, spec;
	calcDiffSpec(lightDir, normal, viewDir, diff, spec);

	vec3 ambient = light.phong.ambient * diffuseMap;
	vec3 diffuse = light.phong.diffuse * diff * diffuseMap;
	vec3 specular = light.phong.specular * spec * specularMap;

	return (ambient + diffuse + specular);
}