#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#include <assimp/Importer.hpp>

#include <stack>

#include "../Helper/opengl_helper.h"
#include "../Helper/image.h"

enum TextureType
{
	Diffuse,
	Specular,
	Bump
};

class Texture
{
private:
	GLuint texture;
	GLenum glType;

public:
	TextureType type;

	Texture(TextureType type = TextureType::Diffuse);

	GLuint getId();
	void allocate();

	void bind(int unit = 0);
	void dispose();

	void setTextureClamping(GLint mode);
	void setTextureBorderColor(float color[]);
	void setTextureFiltering(bool magnify, GLint filter);

	void generateMipmap();

	void set2DImage(Image& image);
	void setDepthComponent(GLsizei width, GLsizei height);
};