#include "AudioTester.h"
#include <AudioManager.h>
#include <iostream>

AudioTester::AudioTester()
{
	AudioManager * am = AudioManager::getInstance();

	am->loadSound("sound", "Sounds/build.wav");
	s = am->getSound("sound");

	am->loadMusic("music", "Sounds/music.wav");
	m = am->getMusic("music");

	PlaySound * ps = new PlaySound(this);
	PlayMusic * pm = new PlayMusic(this);

	InputController::getInstance()->bindKey(SDLK_n, ps);
	InputController::getInstance()->bindKey(SDLK_m, pm);
}


AudioTester::~AudioTester()
{
}

void PlaySound::whenPressed()
{
	owner->s->Play();
}

void PlayMusic::whenPressed()
{
	if (!AudioManager::isMusicPlaying())
		owner->m->Play();
	else
		owner->m->Stop();
}
