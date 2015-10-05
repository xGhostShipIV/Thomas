#pragma once
#include <map>
#include <string>
#include<SDL_mixer.h>

#include "Sound.h"
#include "Music.h"

class AudioManager
{
public:
	~AudioManager();

	static AudioManager * instance;

	//Class is a singleton. This method makes it so!
	static AudioManager * getInstance()
	{
		if (!instance) instance = new AudioManager();
		return instance;
	}

	void loadSound(std::string _id, std::string _fileName);
	Sound * getSound(std::string _id);

	void loadMusic(std::string _id, std::string _fileName);
	Music * getMusic(std::string _id);

private:
	AudioManager();

	std::map<std::string, Sound *> Sounds;
	std::map<std::string, Music *> Musics;

};

