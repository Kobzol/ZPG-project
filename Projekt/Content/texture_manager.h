#pragma once

#include "content_manager.h"
#include "../Model/texture.h"

class TextureManager : public ContentManager<Texture>
{
public:
	static TextureManager& getInstance();

private:
	static TextureManager instance;
};