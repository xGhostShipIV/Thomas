#include "Music.h"
#include "AudioManager.h"


Music::Music(const char * fileName_, int numLoops_)
{
	Audio->system->createStream(fileName_, FMOD_DEFAULT, 0, &music);
	music->setLoopCount(numLoops_);
}

Music::~Music()
{
	music->release();
}

void Music::Play()
{
	bool isMusicPlaying;
	Audio->musicChannel->getPaused(&isMusicPlaying);

	if (!isMusicPlaying)
	{
		Audio->system->playSound(music, 0, false, &(Audio->musicChannel));
	}
	else
	{
		Audio->musicChannel->stop();
		Audio->system->playSound(music, 0, false, &(Audio->musicChannel));
	}
}

void Music::Stop()
{
	Audio->musicChannel->stop();
}

void Music::Pause()
{
	Audio->musicChannel->setPaused(true);
}

void Music::Resume()
{
	bool isPaused;
	Audio->musicChannel->getPaused(&isPaused);
	
	if (isPaused)
	{
		Audio->musicChannel->setPaused(false);
	}
}

void Music::setLoops(int _loops)
{
	isLooped = _loops;
}
