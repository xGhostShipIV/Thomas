#include "Sound.h"
#include <SDL_mixer.h>
#include "AudioManager.h"
#include <fmod_studio.h>
#include <fmod.h>

//Sound::Sound(Mix_Chunk * _sound)
//{
//	sound = _sound;
//}

Sound::Sound(const char * fileName_)
{
	AudioManager::getInstance()->system->createSound(fileName_, FMOD_2D, 0, &sound);
}


Sound::~Sound()
{
	sound->release();
}

void Sound::Play()
{
	AudioManager::getInstance()->system->playSound(sound, 0, false, 0);
}
