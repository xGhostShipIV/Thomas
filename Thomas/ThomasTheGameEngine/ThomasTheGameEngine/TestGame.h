//Author:	Mathieu Violette
//Date:		6/6/2015(MV)
//Testbed for Game Engine

class TestGame;

#define GAMETYPE TestGame
#include "Game.h"

#ifndef TEST_GAME_H
#define TEST_GAME_H

#include "TestLevel.h"
#include "closeGameInput.h"

class TestGame : public Game<TestGame>
{

public:

	TestGame()
	{
		instance = this;

		inputManager = InputController::getInstance();
		
		CloseGame* Exit_Input = new CloseGame();
		inputManager->bindKey(SDLK_ESCAPE, Exit_Input);

		GLU::OutputOpenGLVersion();

		program = GLU::UseShaders("testGame.vert", "testGame.frag");
				
		LoadLevel(new TestLevel(program));
	}
	
	~TestGame()
	{
	}

protected:

	/* Game Update Code Here */
	void Update(UINT32)
	{
		/*if (Input::Keydown_W())
			currentLevel->currentCamera->CameraPosition.z += 0.1f;

		if (Input::Keydown_S())
			currentLevel->currentCamera->CameraPosition.z -= 0.1f;

		if (Input::Keydown_A())
			currentLevel->currentCamera->CameraPosition.x += 0.1f;

		if (Input::Keydown_D())
			currentLevel->currentCamera->CameraPosition.x -= 0.1f;

		if (Input::Keydown_SPACE())
			currentLevel->currentCamera->CameraPosition.y += 0.1f;

		if (Input::Keydown_X())
			currentLevel->currentCamera->CameraPosition.y -= 0.1f;*/



	}

	/* Game Render Code Here */
	void Render()
	{		
	}
};

#endif