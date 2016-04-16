#include "AudioManager.h"
#include "GameProperties.h"

AudioManager * AudioManager::instance;

AudioManager::AudioManager() : soundVolume(1), musicVolume(1), mainVolume(1)
{
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);

	result = FMOD::System_Create(&system);
	result = system->init(512, FMOD_INIT_NORMAL, 0);
}


AudioManager::~AudioManager()
{
	for (auto it = Sounds.begin(); it != Sounds.end(); it++)
	{
		delete it->second;
	}

	for (auto it = Musics.begin(); it != Musics.end(); it++)
	{
		delete it->second;
	}

	system->release();

	Mix_CloseAudio();
}

void AudioManager::loadMusic(std::string _id, std::string _fileName)
{
	Music * m = new Music(_fileName.c_str());
	Musics.insert(std::pair<std::string, Music *>(_id, m));
}

Music * AudioManager::getMusic(std::string _id)
{
	return Musics.find(_id)->second;
}

void AudioManager::loadSound(std::string _id, std::string _fileName)
{
	Sound * newSound = new Sound(_fileName.c_str());
	Sounds.insert(std::pair<std::string, Sound *>(_id, newSound));
}

Sound * AudioManager::getSound(std::string _id)
{
	return Sounds.find(_id)->second;
}

void AudioManager::setMainVolume(float _volume)
{
	mainVolume = _volume <= 1 && _volume >= 0 ? _volume : mainVolume;
	musicChannel->setVolume(getMusicVolume());
}

void AudioManager::setSoundVolume(float _volume)
{
	soundVolume = _volume <= 1 && _volume >= 0 ? _volume : soundVolume;
	//Mix_Volume(-1, MIX_MAX_VOLUME * _volume);
}

void AudioManager::setMusicVolume(float _volume)
{
	musicVolume = _volume <= 1 && _volume >= 0 ? _volume : musicVolume;

	//Mix_VolumeMusic(MIX_MAX_VOLUME * _volume);
	musicChannel->setVolume(getMusicVolume());
}

bool AudioManager::isMusicPlaying()
{
	return (Mix_PlayingMusic() != 0);
}

float AudioManager::getSoundVolume() const
{
	return soundVolume * mainVolume;
}

float AudioManager::getMusicVolume() const
{
	return musicVolume * mainVolume;
}