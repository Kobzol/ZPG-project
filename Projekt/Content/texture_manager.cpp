#include "texture_manager.h"

TextureManager TextureManager::instance = TextureManager();

TextureManager& TextureManager::getInstance()
{
	return TextureManager::instance;
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