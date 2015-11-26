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

TestGame::TestGame()
{
	instance = this;

	inputManager = InputController::getInstance();

	LoadLevel(new TestLevel());

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
		ss << "Test Game | FPS: " << FPS;
		string _fps = ss.str();

		SDL_SetWindowTitle(gameWindow, _fps.c_str());
	}
}

void TestGame::Render()
{

}