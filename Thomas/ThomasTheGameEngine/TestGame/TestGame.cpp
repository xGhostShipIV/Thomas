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

	CloseGame* Exit_Input = new CloseGame(new GameObject(GAME->currentLevel));
	inputManager->bindKey(SDLK_ESCAPE, Exit_Input);

	GLU::OutputOpenGLVersion();
}

TestGame::~TestGame()
{

}

void TestGame::Update(Uint32 _timestep)
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