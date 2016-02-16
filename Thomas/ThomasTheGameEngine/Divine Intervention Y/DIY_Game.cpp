//Author:	Mathieu Violette
//Date:		10/22/2015

#include "DIY_Game.h"
#include <sstream>
#include <OpenGLUtilities.h>
#include <Camera.h>
#include <GameObject.h>
#include <InputHandler.h>
#include <GameProperties.h>
#include <AudioManager.h>

#include <Component.h>
#include <map>
#include <vector>
#include <../Math/four_dimensions.hpp>
#include <SDL.h>

#include "DIY_Level.h"
#include "SplashScreen.h"

DIY_Game::DIY_Game()
{
	instance = this;

	inputManager = InputController::getInstance();

	LoadLevel(new SplashScreen());

	//LoadLevel(new DIY_Level("testLevel.xml"));

	GLU::OutputOpenGLVersion();
}

DIY_Game::~DIY_Game()
{

}

void DIY_Game::Update(float _timestep)
{
	if (Input->isKeyDown(SDLK_ESCAPE))
		GAME->setRunning(false);

	//FPS
	{
		std::stringstream ss;
		ss << "Divine Intervention Y | FPS: " << FPS;
		std::string _fps = ss.str();

		SDL_SetWindowTitle(gameWindow, _fps.c_str());
	}
}

void DIY_Game::Render()
{

}