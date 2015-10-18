#version 330 core

struct VertexData {
	vec4 worldPosition;
	vec3 outNormal;
	vec2 texCoords;
};

struct Phong {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct DirectionalLight {
	vec3 direction;
	Phong phong;
};

in VertexData outVertex;

out vec4 outColor;

uniform sampler2D texture_diffuse;

uniform DirectionalLight directionalLight;

uniform vec3 viewPosition;

void main()
{
	vec4 lightPosition = vec4(-10.0f, 10.0f, 10.0f, 1.0f);
	vec3 ambient = vec3(0.1f, 0.1f, 0.1f);

	vec3 lightDir = normalize(-directionalLight.direction);
	float dotLight = max(dot(lightDir, normalize(outVertex.outNormal)), 0.0f);
	
	vec3 color = vec3(texture(texture_diffuse, outVertex.texCoords));

	vec3 diffColor = dotLight * color;
	vec3 ambientColor = ambient;

	outColor = vec4(diffColor + ambientColor, 1.0f);
}