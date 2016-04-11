#pragma once

#include <fmod.hpp>

struct Mix_Chunk;

class Sound
{
	friend class AudioManager;

public:
	~Sound();

	void Play();

private:
	//Sounds must be created via the AudioManager
	Sound(const char * fileName);

	FMOD::Sound * sound;
};

