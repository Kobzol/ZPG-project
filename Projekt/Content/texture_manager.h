#pragma once

#include <string>

#include "content_manager.h"
#include "../Model/texture.h"

class TextureManager : public ContentManager<Texture>
{
public:
	const static std::string TEXTURE_CROSSHAIR;

	static TextureManager& getInstance();

	void preloadTextures();

	void dispose();

private:
	static TextureManager instance;

	TextureManager();
};