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

private:
	static AudioManager instance;

	AudioManager();

	irrklang::ISoundEngine* engine;
};