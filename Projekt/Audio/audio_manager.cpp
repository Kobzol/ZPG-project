#include "audio_manager.h"

const std::string AudioManager::AUDIO_TEST = "test.mp3";

AudioManager AudioManager::instance = AudioManager();

AudioManager& AudioManager::getInstance()
{
	return AudioManager::instance;
}

AudioManager::AudioManager() : engine(nullptr)
{
	
}

void AudioManager::initialize()
{
	this->engine = irrklang::createIrrKlangDevice();
	assert(this->engine != nullptr);
}
void AudioManager::dispose()
{
	this->engine->drop();
	this->engine = nullptr;
}