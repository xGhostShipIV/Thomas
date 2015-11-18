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

int timeStart, timeSinceLastFPSUpdate, timeSinceLastUpdate, updatesCount;
float deltaTime;

TestGame::TestGame()
{
	instance = this;

	inputManager = InputController::getInstance();

	//Totally overlook and ignore the gameobject added here
	CloseGame* Exit_Input = new CloseGame(new GameObject());

	inputManager->bindKey(SDLK_ESCAPE, Exit_Input);

	LoadLevel(new TestLevel());

	//FPS
	{
		timeSinceLastUpdate = timeStart = glutGet(GLUT_ELAPSED_TIME);
		updatesCount = 0;
		timeSinceLastFPSUpdate = timeStart;
	}
}

TestGame::~TestGame()
{

}

void TestGame::Update(Uint32 _timestep)
{
	//FPS
	{
		int updateTime = glutGet(GLUT_ELAPSED_TIME);
		timeSinceLastUpdate = updateTime;
		updatesCount++;

		if (updatesCount >= 10)
		{
			float fps = updatesCount / ((float)(updateTime - timeSinceLastFPSUpdate) / 1000.f);
			timeSinceLastFPSUpdate = updateTime;
			updatesCount = 0;

			std::stringstream ss;
			ss << "Test Game | FPS: " << fps;
			string _fps = ss.str();

			SDL_SetWindowTitle(gameWindow, _fps.c_str());
		}
	}
}

void TestGame::Render()
{

}