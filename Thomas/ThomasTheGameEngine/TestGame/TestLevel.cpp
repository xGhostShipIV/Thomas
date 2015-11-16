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
	lilCube = GameObject();
	lilCube.position = Vec3(3, 0, 0);
	//lilCube.scale = (Vec3(0.3f, 0.3f, 0.3f));
	light = new GameObject(Vec3(-2, 8, 0));

	cube.addChild(&lilCube);

	at = new AudioTester();
	gameObjects.push_back(at);
	gameObjects.push_back(&cube);
	gameObjects.push_back(&lilCube);
	gameObjects.push_back(light);

	ModelManager::getInstance()->CreateCuboid("idgaf", 0.5f, 0.5f, 0.5f);
	ModelManager::getInstance()->CreatePyramid("igaf", .5f, .5f, .5f);

	float pixelData[]
	{
		0.0f, 1.0f, 0.0f,	1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,	0.0f, 1.0f, 0.0f
	};
	ModelManager::getInstance()->createTexture("greenCheckers", pixelData, 2, 2);

	cubey = new RenderableComponent("idgaf", "greenCheckers", &cube);
	lilCubey = new RenderableComponent("igaf", "greenCheckers", &lilCube);
	
	light->LookAt(Vec3());
	spotLight = new Light(light, Vec4(1.8f, 1.8f, 1.8f, 1.0f), Light::Spot);
	
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
}

TestLevel::~TestLevel(){}

void TestLevel::LevelUpdate(UINT32 _timeStep)
{
	Level::LevelUpdate(_timeStep);

	cube.GetTransform().Rotate(Quat(0.01570796f, Vec3(0, 1, 0)));
}

void TestLevel::DebugRender()
{
	/*cubey->DrawModel();
	cubey->DrawWireframe();*/
}
