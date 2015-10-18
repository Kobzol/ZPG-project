#include "cubemap.h"

Cubemap::Cubemap() : cubemap(0)
{

}

void Cubemap::allocate()
{
	glGenTextures(1, &this->cubemap);
	GL_CHECK_ERRORS();
}
void Cubemap::dispose()
{
	if (this->cubemap != 0)
	{
		glDeleteTextures(1, &this->cubemap);
		GL_CHECK_ERRORS();
	}
}

void Cubemap::bind(int unit)
{
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_CUBE_MAP, this->cubemap);
	GL_CHECK_ERRORS();
}
GLuint Cubemap::getId()
{
	return this->cubemap;
}

void Cubemap::set2DImages(std::vector<Image>& images)
{
	this->bind();

	for (size_t i = 0; i < images.size(); i++)
	{
		GLenum type = (images[i].type == ImageType::Alpha) ? GL_RGBA : GL_RGB;

		glTexImage2D(
			GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, type,
			images[i].getWidth(), images[i].getHeight(), 0, type, GL_UNSIGNED_BYTE, images[i].getImageData()
		);
		GL_CHECK_ERRORS();
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	GL_CHECK_ERRORS();
}

void Cubemap::generateDepthMap(int width, int height)
{
	this->bind();

	for (size_t i = 0; i < 6; i++)
	{
		glTexImage2D(
			GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT,
			width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL
		);
		GL_CHECK_ERRORS();
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	GL_CHECK_ERRORS();
}