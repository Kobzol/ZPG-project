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