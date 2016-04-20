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

	if (isMusicPlaying)
		Audio->musicChannel->stop();

	Audio->system->playSound(music, 0, true, &(Audio->musicChannel));
	Audio->musicChannel->setVolume(Audio->getMusicVolume());
	Audio->musicChannel->setPaused(false);
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
	Audio->musicChannel->setLoopCount(_loops);
	//isLooped = _loops;
}
