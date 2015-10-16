#include "image.h"

Image::Image(std::string path, ImageType type) : type(type)
{
	this->data = SOIL_load_image(path.c_str(), &width, &height, 0, (type == ImageType::Alpha) ? SOIL_LOAD_RGBA : SOIL_LOAD_RGB);
}
Image::Image(int width, int height, ImageType type) : width(width), height(height), data(nullptr), type(type)
{
	
}

int Image::getWidth()
{
	return this->width;
}
int Image::getHeight()
{
	return this->height;
}
unsigned char* Image::getImageData()
{
	return this->data;
}
void Image::dispose()
{
	if (this->data != nullptr)
	{
		SOIL_free_image_data(this->data);
	}

	this->data = nullptr;
}