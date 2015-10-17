#include "texture_manager.h"

TextureManager TextureManager::instance = TextureManager();

TextureManager& TextureManager::getInstance()
{
	return TextureManager::instance;
}