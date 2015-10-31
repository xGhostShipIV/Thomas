#pragma once

#include <GameObject.h>
#include <InputComponent.h>

class Sound;
class Music;

class AudioTester :
	public GameObject
{
	friend class PlaySound;
	friend class PlayMusic;

public:
	AudioTester();
	~AudioTester();

private:
	Sound * s;
	Music * m;
};

class PlaySound : public InputComponent
{
public:
	AudioTester * owner;

	PlaySound(AudioTester * _a) : InputComponent(_a){
		owner = _a;
	}

	~PlaySound();

	void whenPressed() override;
};

class PlayMusic : public InputComponent
{
public:
	AudioTester * owner;

	PlayMusic(AudioTester * _a) : InputComponent(_a){
		owner = _a;
	}

	~PlayMusic();

	void whenPressed() override;
};
