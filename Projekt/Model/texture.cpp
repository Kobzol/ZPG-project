#include "texture.h"

Texture::Texture(TextureType type) : type(type), texture(0)
{
	this->glType = GL_TEXTURE_2D;
}

void Texture::allocate()
{
	glGenTextures(1, &this->texture);
	GL_CHECK_ERRORS();
}

GLuint Texture::getId()
{
	return this->texture;
}

void Texture::bind(int unit)
{
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(this->glType, this->texture);
	GL_CHECK_ERRORS();
}
void Texture::dispose()
{
	if (this->texture != 0)
	{
		glDeleteTextures(1, &this->texture);
		GL_CHECK_ERRORS();
		this->texture = 0;
	}
}

void Texture::generateMipmap()
{
	glGenerateMipmap(this->glType);
	GL_CHECK_ERRORS();
}

void Texture::setTextureClamping(GLint mode)
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, mode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, mode);

	GL_CHECK_ERRORS();
}
void Texture::setTextureBorderColor(float color[])
{
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color);
	GL_CHECK_ERRORS();
}
void Texture::setTextureFiltering(bool magnify, GLint filter)
{
	glTexParameteri(GL_TEXTURE_2D, magnify ? GL_TEXTURE_MAG_FILTER : GL_TEXTURE_MIN_FILTER, filter);
	GL_CHECK_ERRORS();
}

void Texture::set2DImage(Image& image)
{
	GLint format = (image.type == ImageType::Alpha) ? GL_RGBA : GL_RGB;

	glTexImage2D(this->glType, 0, format, image.getWidth(), image.getHeight(), 0, format, GL_UNSIGNED_BYTE, image.getImageData());
	GL_CHECK_ERRORS();
}
void Texture::setDepthComponent(GLsizei width, GLsizei height)
{
	glTexImage2D(this->glType, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
	GL_CHECK_ERRORS();
}