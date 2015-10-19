#pragma once

#include <cassert>
#include <string>

#include <irrKlang.h>

class AudioManager
{
public:
	static const std::string AUDIO_TEST;

	static AudioManager& getInstance();

	void initialize();
	void dispose();

	void play2DForget(std::string path);

	void setVolume(float volume);

private:
	static const std::string AUDIO_PATH;

	static AudioManager instance;

	AudioManager();

	irrklang::ISoundEngine* engine;
};