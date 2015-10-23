//Author:	Mathieu Violette
//Date:		10/22/2015

#include "TestGame.h"
#include "TestLevel.h"
#include "GameObject.h"
#include "Input.h"
#include "InputComponent.h"
#include "GameProperties.h"
#include "AudioManager.h"
#include "Camera.h"
#include "OpenGLUtilities.h"
#include "closeGameInput.h"

TestGame::TestGame()
{
	instance = this;

	inputManager = InputController::getInstance();

	CloseGame* Exit_Input = new CloseGame();
	inputManager->bindKey(SDLK_ESCAPE, Exit_Input);

	GLU::OutputOpenGLVersion();

	program = GLU::UseShaders("testGame.vert", "testGame.frag");

	LoadLevel(new TestLevel(program));
}

TestGame::~TestGame()
{

}

void TestGame::Update(Uint32 _timestep)
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

void TestGame::Render()
{

}