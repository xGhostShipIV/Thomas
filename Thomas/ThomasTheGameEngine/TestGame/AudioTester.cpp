#include "AudioTester.h"
#include <AudioManager.h>
#include <iostream>

AudioTester::AudioTester(Level * _level) : GameObject(_level)
{
	AudioManager * am = AudioManager::getInstance();

	am->loadSound("sound", "Sounds/build.wav");
	s = am->getSound("sound");

	am->loadMusic("music", "Sounds/music.wav");
	m = am->getMusic("music");

	new PlaySound(this, SDLK_n);
	new PlayMusic(this, SDLK_m);
}


AudioTester::~AudioTester()
{
}

void PlaySound::whenPressed(float _timestep)
{
	owner->s->Play();
}

void PlayMusic::whenPressed(float _timestep)
{
	if (!AudioManager::isMusicPlaying())
		owner->m->Play();
	else
		owner->m->Stop();
}
