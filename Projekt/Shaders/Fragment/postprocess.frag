#version 330 core
in vec2 TexCoords;

out vec4 color;

uniform sampler2D screenTexture;

uniform int postProcess;

vec4 apply_kernel(in float kernel[9], float strength);

void main()
{ 
	vec4 texColor = vec4(1.0f);

	if (postProcess == 0)
	{
		texColor = texture(screenTexture, TexCoords);
	}
	else if (postProcess == 1)
	{
		float kernel[9] = float[]( // blur
			1.0f / 16.0f, 2.0f / 16.0f, 1.0f / 16.0f,
			2.0f / 16.0f, 4.0f / 16.0f, 2.0f / 16.0f,
			1.0f / 16.0f, 2.0f / 16.0f, 1.0f / 16.0f  
		);

		texColor = apply_kernel(kernel, 1.0f);
	}
	else if (postProcess == 2)
	{
		float kernel[9] = float[]( // edge detection
			1.0f, 1.0f, 1.0f,
			1.0f, -8.0f, 1.0f,
			1.0f, 1.0f, 1.0f
		);

		texColor = apply_kernel(kernel, 1.0f);
	}

	color = vec4(texColor);
}

vec4 apply_kernel(in float kernel[9], float strength)
{
	float offset = strength / 100.0f;

	vec2 offsets[9] = vec2[](
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

	vec3 sampleTex[9];

    for(int i = 0; i < 9; i++)
    {
        sampleTex[i] = vec3(texture(screenTexture, TexCoords.st + offsets[i]));
    }
    
	vec3 col = vec3(0.0f);
    
	for(int i = 0; i < 9; i++)
	{
        col += sampleTex[i] * kernel[i];
	}
    
    return vec4(col, 1.0f);
}