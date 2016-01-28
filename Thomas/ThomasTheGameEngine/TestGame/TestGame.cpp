//Author:	Mathieu Violette
//Date:		10/22/2015

#include "TestGame.h"
#include "TestLevel.h"
#include <GameObject.h>
#include <InputComponent.h>
#include <GameProperties.h>
#include <AudioManager.h>
#include <Camera.h>
#include "closeGameInput.h"
#include <sstream>
#include "Observatory.h"
#include "DrScottLevel.h"
#include "TestNetLevel.h"
#include "UITestLevel.h"

TestGame::TestGame()
{
	instance = this;

	inputManager = InputController::getInstance();

	//LoadLevel(new Observatory());
	//LoadLevel(new TestLevel());
	//LoadLevel(new DrScottLevel());
	
	//LoadLevel(new TestNetLevel());

	LoadLevel(new UITestLevel());

	new CloseGame(new GameObject(GAME->currentLevel), SDLK_ESCAPE);

	GLU::OutputOpenGLVersion();
}

TestGame::~TestGame()
{

}

void TestGame::Update(float _timestep)
{
	//FPS
	{
		std::stringstream ss;
		ss << "Thomas Demo | FPS: " << FPS;
		string _fps = ss.str();

		SDL_SetWindowTitle(gameWindow, _fps.c_str());
	}
}

void TestGame::Render()
{

}