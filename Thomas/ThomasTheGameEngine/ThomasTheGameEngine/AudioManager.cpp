#include "AudioManager.h"

AudioManager * AudioManager::instance;

AudioManager::AudioManager()
{
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
}


AudioManager::~AudioManager()
{
	for (auto it = Sounds.end(); it != Sounds.begin(); it--)
	{
		delete it->second;
	}

	for (auto it = Musics.end(); it != Musics.begin(); it--)
	{
		delete it->second;
	}

	Mix_CloseAudio();
}

void AudioManager::loadMusic(std::string _id, std::string _fileName)
{
	Music * m = new Music(Mix_LoadMUS(_fileName.c_str()));
	Musics.insert(std::pair<std::string, Music *>(_id, m));
}

Music * AudioManager::getMusic(std::string _id)
{
	return Musics.find(_id)->second;
}

void AudioManager::loadSound(std::string _id, std::string _fileName)
{
	
	Sound * newSound = new Sound(Mix_LoadWAV(_fileName.c_str()));
	Sounds.insert(std::pair<std::string, Sound *>(_id, newSound));
}

Sound * AudioManager::getSound(std::string _id)
{
	return Sounds.find(_id)->second;
}
