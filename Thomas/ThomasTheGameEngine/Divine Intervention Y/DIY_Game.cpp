//Author:	Mathieu Violette
//Date:		10/22/2015

#include "DIY_Game.h"
#include <sstream>
#include <OpenGLUtilities.h>
#include <Camera.h>
#include <GameObject.h>
#include <InputComponent.h>
#include <GameProperties.h>
#include <AudioManager.h>

#include "DIY_Level.h"

DIY_Game::DIY_Game()
{
	instance = this;

	inputManager = InputController::getInstance();

	LoadLevel(new DIY_Level("testLevel.xml"));

	GLU::OutputOpenGLVersion();
}

DIY_Game::~DIY_Game()
{

}

void DIY_Game::Update(float _timestep)
{
	//FPS
	{
		std::stringstream ss;
		ss << "Thomas Demo | FPS: " << FPS;
		std::string _fps = ss.str();

		SDL_SetWindowTitle(gameWindow, _fps.c_str());
	}
}

void DIY_Game::Render()
{

}