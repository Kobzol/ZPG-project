#version 330 core

struct VertexData {
	vec4 worldPosition;
	vec3 outNormal;
	vec2 texCoords;
};

in VertexData outVertex;

out vec4 outColor;

uniform sampler2D texture_diffuse;

void main()
{
	vec4 lightPosition = vec4(-10.0f, 10.0f, 10.0f, 1.0f);
	vec4 ambient = vec4(0.1f, 0.1f, 0.1f, 1.0f);

	vec3 lightDir = vec3(normalize(lightPosition));
	float dotLight = max(dot(lightDir, normalize(outVertex.outNormal)), 0.0f);
	
	vec4 color = texture(texture_diffuse, outVertex.texCoords);

	vec4 diffColor = dotLight * color;
	vec4 ambientColor = ambient;

	outColor = diffColor + ambientColor;
}