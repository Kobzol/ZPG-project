#pragma once

#include <string>

#include "SOIL.h"

enum ImageType
{
	NoAlpha,
	Alpha
};

class Image
{
private:
	int width;
	int height;
	unsigned char* data;

public:
	ImageType type;

	Image(std::string path, ImageType type = ImageType::Alpha);
	Image(int width, int height, ImageType type = ImageType::Alpha);

	int getWidth();
	int getHeight();

	unsigned char* getImageData();
	void free();
};