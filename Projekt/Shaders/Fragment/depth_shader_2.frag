#version 330 core

in VertexParams {
	vec3 FragPos;
	vec3 Normal;
	vec2 TexCoords;
	vec4 FragPosLightSpace;
} params_in;

out vec4 outColor;

uniform sampler2D diffuseTexture;
uniform sampler2D shadowMap;

uniform vec3 lightPos;
uniform vec3 viewPos;

float ShadowCalculation(vec4 fragPosLightSpace, vec3 normal, vec3 lightDir)
{
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
	projCoords = projCoords * 0.5f + 0.5f;

	if (projCoords.z > 1.0f)
	{
		return 0.0f;
	}

	float closestDepth = texture(shadowMap, projCoords.xy).r;
	float currentDepth = projCoords.z;

	float bias = max(0.05f * (1.0 - dot(normal, lightDir)), 0.005f);	// shadow bias
	//float shadow = currentDepth - bias > closestDepth ? 1.0f : 0.0f;

	float shadow = 0.0;
	vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
	for (int x = -1; x <= 1; ++x)
	{
		for (int y = -1; y <= 1; ++y)
		{
			float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r; 
			shadow += currentDepth - bias > pcfDepth ? 1.0f : 0.0f;        
		}    
	}
	shadow /= 9.0f;

	return shadow;
}

void main()
{
	vec3 color = texture(diffuseTexture, params_in.TexCoords).rgb;
	vec3 normal = normalize(params_in.Normal);
    vec3 lightColor = vec3(1.0f);

    // Ambient
    vec3 ambient = 0.15f * color;

    // Diffuse
    vec3 lightDir = normalize(lightPos - params_in.FragPos);
    float diff = max(dot(lightDir, normal), 0.0f);
    vec3 diffuse = diff * lightColor;

    // Specular
    vec3 viewDir = normalize(viewPos - params_in.FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = 0.0f;
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    spec = pow(max(dot(normal, halfwayDir), 0.0f), 64.0f);
    vec3 specular = spec * lightColor;

    // Calculate shadow
    float shadow = ShadowCalculation(params_in.FragPosLightSpace, normal, lightDir);       
    vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular)) * color;    
    
    outColor = vec4(lighting, 1.0f);
}