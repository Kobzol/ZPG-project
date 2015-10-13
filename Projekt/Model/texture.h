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
	Specular
};

class Texture
{
private:
	static std::stack<GLuint> bindings;

	GLuint texture;

public:
	static void saveState();
	static void restoreState();

	TextureType type;
	GLenum glType;

	Texture(TextureType type = TextureType::Diffuse);

	GLuint getId();
	void allocate();

	void bind(int unit = 0);
	void free();

	void setTextureClamping(GLint mode);
	void setTextureBorderColor(float color[]);
	void setTextureFiltering(bool magnify, GLint filter);

	void generateMipmap();

	void set2DImage(Image& image);
	void setDepthComponent(GLsizei width, GLsizei height);
};