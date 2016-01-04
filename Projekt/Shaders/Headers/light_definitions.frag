struct Attenuation {
	float constant;
	float linear;
	float quadratic;
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
struct PointLight {
    vec3 position;

	Attenuation attenuation;
    Phong phong;
};
struct SpotLight {
	vec3 position;
    vec3 direction;
	float cutOff;
	float outerCutOff;

	Attenuation attenuation;
	Phong phong;
};

uniform DirLight directionalLight;

#define MAX_POINT_LIGHTS 3
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform int pointLightCount;

#define MAX_SPOT_LIGHTS 1
uniform SpotLight spotLights[MAX_SPOT_LIGHTS];
uniform int spotLightCount;