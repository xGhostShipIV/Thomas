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

TestGame::TestGame()
{
	instance = this;

	inputManager = InputController::getInstance();

	//Totally overlook and ignore the gameobject added here
	CloseGame* Exit_Input = new CloseGame(new GameObject());

	inputManager->bindKey(SDLK_ESCAPE, Exit_Input);

	LoadLevel(new TestLevel());
}

TestGame::~TestGame()
{

}

void TestGame::Update(Uint32 _timestep)
{

}

void TestGame::Render()
{

}