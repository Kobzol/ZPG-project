#pragma once

#include "content_manager.h"
#include "../Model/texture.h"

class TextureManager : public ContentManager<Texture>
{
public:
	static TextureManager& getInstance();

	void dispose();

private:
	static TextureManager instance;

	TextureManager();
};