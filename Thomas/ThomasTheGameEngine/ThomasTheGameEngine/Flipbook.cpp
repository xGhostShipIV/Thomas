//Author: Nathan Senter
//Date: 01/12/2015

#include "GameObject.h"
#include "Flipbook.h"
#include "ModelManager.h"
#include "RenderableComponent.h"

/* _filePath should be the path to the first image of the 2D animation, and all files should be named in the format of
	"imageNamei.extension", where i is the index of the image in the animation. */
Flipbook::Flipbook(GameObject * _owner, unsigned int _numImages, std::string _filePath, float _playTime, bool _isLooped, Image_Extension _ext) : Component(_owner, ComponentType::Flipbook)
{
	numFrames = _numImages;
	totalPlayTime = _playTime;

	timePerFrame = _playTime / (float)numFrames;

	elapsedTime = 0.0f;
	timeSinceLastFrame = 0.0f;

	currentFrame = 0;

	isRunning = false;
	isLooped = _isLooped;

	//LOADING AND ASSIGNING TEXTURE DATA
	ModelManager * mm = ModelManager::getInstance();

	for (int i = 0; i < numFrames; i++)
	{
		std::string subString = _filePath;

		if (_ext == PNG || _ext == JPG || _ext == TIF) subString = subString.substr(0, subString.length() - 5);
		else subString = subString.substr(0, subString.length() - 6);

		switch (_ext)
		{
		case Flipbook::PNG:
			subString += std::to_string(i) + ".png";

			mm->loadTexture(subString, subString);
			textureNames.push_back(subString);
			break;
		case Flipbook::JPG:
			subString += std::to_string(i) + ".jpg";

			mm->loadTexture(subString, subString);
			textureNames.push_back(subString);
			break;
		case Flipbook::JPEG:
			subString += std::to_string(i) + ".jpeg";

			mm->loadTexture(subString, subString);
			textureNames.push_back(subString);
			break;
		case Flipbook::TIF:
			subString += std::to_string(i) + ".tif";

			mm->loadTexture(subString, subString);
			textureNames.push_back(subString);
			break;
		default:
			break;
		}
	}

	ownerRenderer = parentObject->getComponent<RenderableComponent>();
	ownerRenderer->SetTextureID(textureNames[0], 0);
}

//Start the animation
void Flipbook::Play()
{
	isRunning = true;
}

//Stop the animation and reset the current frame to 0
void Flipbook::Stop()
{
	isRunning = false;
	currentFrame = 0;
}

//Stop the animation without resetting the current frame
void Flipbook::Pause()
{
	isRunning = false;
}

void Flipbook::UpdateFlipbook(float _deltaTime)
{
	//A safeguard
	if (ownerRenderer)
	{
		if (isRunning)
		{
			//Check if it is time to update to a new image
			//if (timeSinceLastFrame >= timePerFrame)
			if (timeSinceLastFrame >= timePerFrame)
			{
				currentFrame = ++currentFrame % numFrames;
				ownerRenderer->SetTextureID(textureNames[currentFrame], 0);

				timeSinceLastFrame = 0.0f;

				if (currentFrame == numFrames - 1 && !isLooped)
					isRunning = false;
			}
			else timeSinceLastFrame += _deltaTime;
		}
	}
}