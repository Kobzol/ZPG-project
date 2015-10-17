#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#include <vector>

#include "../Helper/opengl_helper.h"
#include "../Helper/image.h"

class Cubemap
{
private:
	GLuint cubemap;

public:
	Cubemap();

	GLuint getId();
	void allocate();

	void bind(int unit = 0);
	void dispose();

	void set2DImages(std::vector<Image>& images);

	void generateDepthMap(int width, int height);
};