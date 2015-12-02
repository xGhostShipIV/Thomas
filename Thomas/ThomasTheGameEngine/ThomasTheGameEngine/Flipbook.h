//Author: Nathan Senter
//Date: 01/12/2015

#pragma once

#include "Component.h"
#include <vector>

class RenderableComponent;

class Flipbook : public Component
{
public:
	enum Image_Extension
	{
		PNG, JPG, JPEG, TIF
	};

	Flipbook(GameObject *, unsigned int _numImages, std::string _filePath, float _playTime, bool _isLooped, Image_Extension _ext);
	~Flipbook();

	void Play();
	void Pause();
	void Stop();

	void UpdateFlipbook(float _deltaTime);

private:
	bool isRunning;
	bool isLooped;

	float elapsedTime;

	float timePerFrame;
	float timeSinceLastFrame;
	float totalPlayTime;

	unsigned int numFrames;
	unsigned int currentFrame;

	RenderableComponent * ownerRenderer;

	std::vector<std::string> textureNames;
};