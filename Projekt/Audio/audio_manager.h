#pragma once

#include <cassert>
#include <string>
#include <unordered_map>

#include <irrKlang.h>

class AudioManager
{
public:
	static const std::string AUDIO_GUNSHOT;

	static AudioManager& getInstance();

	void initialize();
	void dispose();

	void play2DForget(std::string path);

	void setVolume(float volume);

private:
	static const std::string AUDIO_PATH;

	static AudioManager instance;

	AudioManager();

	void preloadSounds();
	void preloadSound(std::string path);

	irrklang::ISoundEngine* engine;
	std::unordered_map<std::string, irrklang::ISoundSource*> sounds;
};