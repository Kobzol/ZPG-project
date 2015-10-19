#include "audio_manager.h"

const std::string AudioManager::AUDIO_PATH = "Resources/Sound/";

const std::string AudioManager::AUDIO_GUNSHOT = "gunshot.wav";

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

	this->preloadSounds();
}
void AudioManager::dispose()
{
	this->engine->drop();
	this->engine = nullptr;
}

void AudioManager::play2DForget(std::string path)
{
	path = AudioManager::AUDIO_PATH + path;

	if (this->sounds.count(path))
	{
		this->engine->play2D(this->sounds[path]);
	}
	else this->engine->play2D(path.c_str());
}

void AudioManager::setVolume(float volume)
{
	this->engine->setSoundVolume(volume);
}

void AudioManager::preloadSounds()
{
	this->preloadSound(AudioManager::AUDIO_GUNSHOT);
}
void AudioManager::preloadSound(std::string path)
{
	path = AudioManager::AUDIO_PATH + path;

	if (!this->sounds.count(path))
	{
		this->sounds.emplace(path, this->engine->addSoundSourceFromFile(path.c_str(), irrklang::E_STREAM_MODE::ESM_NO_STREAMING, true));
	}
}