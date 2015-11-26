#pragma once

#include <GameObject.h>
#include <InputComponent.h>

class Sound;
class Music;

/*
A gameobejct created to test both Input as well as the AudioManager
*/

class AudioTester :
	public GameObject
{
	friend class PlaySound;
	friend class PlayMusic;

public:
	AudioTester(Level * _level);
	~AudioTester();

private:
	Sound * s;
	Music * m;
};

//Following is specificly defined inputComponents that will play a
//sound, or music when the right key is pressed
class PlaySound : public InputComponent
{
public:
	AudioTester * owner;

	PlaySound(AudioTester * _a, SDL_Keycode key) : InputComponent(_a, key){
		owner = _a;
	}

	~PlaySound();

	void whenPressed(float _timestep) override;
};

class PlayMusic : public InputComponent
{
public:
	AudioTester * owner;

	PlayMusic(AudioTester * _a, SDL_Keycode key) : InputComponent(_a, key){
		owner = _a;
	}

	~PlayMusic();

	void whenPressed(float _timestep) override;
};
