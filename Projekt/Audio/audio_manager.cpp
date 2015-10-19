#include "audio_manager.h"

const std::string AudioManager::AUDIO_PATH = "Resources/Sound/";

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

void AudioManager::play2DForget(std::string path)
{
	path = AudioManager::AUDIO_PATH + path;
	this->engine->play2D(path.c_str());
}

void AudioManager::setVolume(float volume)
{
	this->engine->setSoundVolume(volume);
}