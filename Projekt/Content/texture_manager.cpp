#include "texture_manager.h"

const std::string TextureManager::TEXTURE_CROSSHAIR = "crosshair";

TextureManager TextureManager::instance = TextureManager();

TextureManager& TextureManager::getInstance()
{
	return TextureManager::instance;
}

void TextureManager::preloadTextures()
{
	Texture crosshairTexture;
	crosshairTexture.allocate();
	crosshairTexture.bind();
	crosshairTexture.set2DImage(Image("Resources/Textures/crosshair.png"));
	crosshairTexture.generateMipmap();
	crosshairTexture.setTextureClamping(GL_CLAMP_TO_EDGE);
	crosshairTexture.setTextureFiltering(false, GL_LINEAR);
	crosshairTexture.setTextureFiltering(true, GL_LINEAR);

	this->load(TextureManager::TEXTURE_CROSSHAIR, crosshairTexture);
}

TextureManager::TextureManager()
{

}

void TextureManager::dispose()
{
	for (auto& texture : this->items)
	{
		texture.second.dispose();
	}
}