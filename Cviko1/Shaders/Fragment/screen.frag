#version 330 core

in vec2 TexCoords;

out vec4 outColor;

uniform sampler2D screenTexture;

const float offset = 1.0f / 300.0f;

vec2 offsets[9] = vec2[] (
    vec2(-offset, offset),  // top-left
    vec2(0.0f,    offset),  // top-center
    vec2(offset,  offset),  // top-right
    vec2(-offset, 0.0f),    // center-left
    vec2(0.0f,    0.0f),    // center-center
    vec2(offset,  0.0f),    // center-right
    vec2(-offset, -offset), // bottom-left
    vec2(0.0f,    -offset), // bottom-center
    vec2(offset,  -offset)  // bottom-right    
);

vec3 invert(vec3 color)
{
	return vec3(1.0f) - color;
}
vec3 grayscale(vec3 color)
{
	float average = 0.2126 * color.r + 0.7152 * color.g + 0.0722 * color.b;
	return vec3(average);
}

vec3 calculateKernel(float kernel[9])
{
	vec3 color = vec3(0.0f);

	for (int i = 0; i < 9; i++)
	{
		color += kernel[i] * vec3(texture(screenTexture, TexCoords + offsets[i]));
	}

	return color;
}

vec3 sharpen()
{
	float kernel[9] = float[] (
        -1.0f, -1.0f, -1.0f,
        -1.0f,  9.0f, -1.0f,
        -1.0f, -1.0f, -1.0f
    );

	return calculateKernel(kernel);
}

vec3 blur()
{
	float kernel[9] = float[] (
        1.0f, 2.0f, 1.0f,
        2.0f,  4.0f, 2.0f,
        1.0f, 2.0f, 1.0f
    );

	return calculateKernel(kernel) / 16.0f;
}

vec3 detect_edges()
{
	float kernel[9] = float[] (
        1.0f, 1.0f, 1.0f,
        1.0f,  -8.0f, 1.0f,
        1.0f, 1.0f, 1.0f
    );

	return calculateKernel(kernel);
}

void main()
{
	vec3 color = detect_edges();
	outColor = vec4(color, 1.0f);
}