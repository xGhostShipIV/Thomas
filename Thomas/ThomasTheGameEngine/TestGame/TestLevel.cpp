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
	cube = GameObject(Vec3(0, 0, 0));
	lilCube = GameObject(Vec3(2, 0, 0));
	//lilCube.scale = (Vec3(0.3f, 0.3f, 0.3f));
	light = GameObject(Vec3(-4, 8, 0));
	soBright = GameObject(Vec3(0, 0, -3));

	//cube.addChild(&lilCube);
	cube.addChild(&soBright);

	at = new AudioTester();
	gameObjects.push_back(at);
	gameObjects.push_back(&cube);
	gameObjects.push_back(&lilCube);
	gameObjects.push_back(&light);
	gameObjects.push_back(&soBright);

	ModelManager::getInstance()->CreateCuboid("idgaf", 0.5f, 0.5f, 0.5f);
	ModelManager::getInstance()->CreatePyramid("igaf", .5f, .5f, .5f);
	ModelManager::getInstance()->CreateCuboid("light", 0.25f, 0.25f, 0.25f);

	float pixelData[]
	{
		0.0f, 1.0f, 0.0f,	1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,	0.0f, 1.0f, 0.0f
	};
	ModelManager::getInstance()->createTexture("greenCheckers", pixelData, 2, 2);

	float pixelDataRed[]
	{
		1.0f, 0.0f, 0.0f,	1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,	1.0f, 0.0f, 0.0f
	};
	ModelManager::getInstance()->createTexture("redCheckers", pixelDataRed, 2, 2);

	cubey = new RenderableComponent("idgaf", "greenCheckers", &cube);
	lilCubey = new RenderableComponent("igaf", "greenCheckers", &lilCube);
	pointyLight = new RenderableComponent("light", "redCheckers", &soBright);

	light.LookAt(Vec3());
	soBright.LookAt(Vec3());

	directionLightOne = new Light(&light, Vec4(.6f, 0.6f, 0.6f, 1.0f), Light::Directional);
	directionLightTwo = new Light(&soBright, Vec4(10, 0, 0, 1.0f), Light::Point, 3.0f);
	
	ambientLightColor = Vec4(0.1, 0.1, 0.1, 1);

	ModelManager::getInstance()->PushModels();

	currentCamera->GetTransform().position = Vec3(0, 0, -8);

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

	
	GameObject_PosX* goPX = new GameObject_PosX(&cube);
	Game::GetInstance()->inputManager->bindKey(SDLK_LEFT, goPX);

	GameObject_NegX* goNX = new GameObject_NegX(&cube);
	Game::GetInstance()->inputManager->bindKey(SDLK_RIGHT, goNX);

	GameObject_ScaleUp* goSU = new GameObject_ScaleUp(&cube);
	Game::GetInstance()->inputManager->bindKey(SDLK_UP, goSU);

	GameObject_ScaleDown* goSD = new GameObject_ScaleDown(&cube);
	Game::GetInstance()->inputManager->bindKey(SDLK_DOWN, goSD);

	AmbientBrightnessUp* abu = new AmbientBrightnessUp(&ambientLightColor);
	Game::GetInstance()->inputManager->bindKey(Game::GetInstance()->inputManager->mouseButtonDict[SDL_BUTTON_LEFT], abu);

	AmbientBrightnessDown* abd = new AmbientBrightnessDown(&ambientLightColor);
	Game::GetInstance()->inputManager->bindKey(Game::GetInstance()->inputManager->mouseButtonDict[SDL_BUTTON_RIGHT], abd);
}

TestLevel::~TestLevel(){}

void TestLevel::LevelUpdate(UINT32 _timeStep)
{
	Level::LevelUpdate(_timeStep);

	//cube.GetTransform().Rotate(Quat(0.01570796f, Vec3(0, 1, 0)));
}

void TestLevel::DebugRender()
{
	/*cubey->DrawModel();
	cubey->DrawWireframe();*/
}

