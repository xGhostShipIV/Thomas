#pragma once
#include <SDL_mixer.h>
#include <fmod.hpp>

class Music
{
	friend class AudioManager;

public:
	~Music();

	void Play();
	void Stop();
	void Pause();
	void Resume();

	void setLoops(int);

private:
	Music(const char * fileName_, int numLoops_ = -1);


	FMOD::Sound * music;
	int isLooped;
};

