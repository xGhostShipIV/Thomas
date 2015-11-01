//Author:	Mathieu Violette
//Date:		10/21/2015
//Example Level

#include "TestLevel.h"


#define BUFFER_OFFSET(i) ((void*)(i))

enum VAO_IDs { Triangles, NumVAOs };
enum Buffer_IDs { ArrayBuffer, NumBuffers };
enum Attrib_IDs { vPosition = 0 };

GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];

TestLevel::TestLevel()
{
	cube = GameObject();
	at = new AudioTester();
	gameObjects.push_back(at);
	gameObjects.push_back(&cube);

	ModelManager::getInstance()->CreateCuboid("idgaf", 0.5f, 0.5f, 0.5f);
	cubey = new RenderableComponent("idgaf", &cube);

	ModelManager::getInstance()->PushModels();

	currentCamera->GetTransform().position = Vec3(0, 0, -2);

	//Setup the input controller here
	CameraUp* cU = new CameraUp(currentCamera);
	Game::GetInstance()->inputManager->bindKey(SDLK_SPACE, cU);

	CameraDown* cD = new CameraDown(currentCamera);
	Game::GetInstance()->inputManager->bindKey(SDLK_x, cD);

	CameraRight* cR = new CameraRight(currentCamera);
	Game::GetInstance()->inputManager->bindKey(SDLK_d, cR);

	CameraLeft* cL = new CameraLeft(currentCamera);
	Game::GetInstance()->inputManager->bindKey(SDLK_a, cL);

	CameraForward* cF = new CameraForward(currentCamera);
	Game::GetInstance()->inputManager->bindKey(SDLK_w, cF);

	CameraBackward* cB = new CameraBackward(currentCamera);
	Game::GetInstance()->inputManager->bindKey(SDLK_s, cB);

	CameraTurnLeft* cTL = new CameraTurnLeft(currentCamera);
	Game::GetInstance()->inputManager->bindKey(SDLK_q, cTL);

	CameraTurnRight* cTR = new CameraTurnRight(currentCamera);
	Game::GetInstance()->inputManager->bindKey(SDLK_e, cTR);

	CameraTurnDown* cTD = new CameraTurnDown(currentCamera);
	Game::GetInstance()->inputManager->bindKey(SDLK_c, cTD);

	CameraTurnUp* cTU = new CameraTurnUp(currentCamera);
	Game::GetInstance()->inputManager->bindKey(SDLK_z, cTU);
}

TestLevel::~TestLevel(){}

void TestLevel::LevelUpdate(UINT32 _timeStep)
{
	Level::LevelUpdate(_timeStep);

	cube.GetTransform().Rotate(Quat(0.1570796f, Vec3(0, 1, 0)));
}

void TestLevel::DebugRender()
{
	cubey->DrawModel();
	cubey->DrawWireframe();
}
