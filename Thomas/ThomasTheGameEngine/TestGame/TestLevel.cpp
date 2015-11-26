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
	currentCamera->position = Vec3(0, 1, -8);

	ambientLightColor = Vec4(1, 0.1, 0.1, 0.1);

	new AudioTester(this);

	cube = new GameObject(this, Vec3(0, 0.5f, 0));
	lilCube = new GameObject(this, Vec3(2, 0.5f, 0));
	light = new GameObject(this, Vec3(0, 14, 30));
	lightAnchor = new GameObject(this, Vec3());
	soBright = new GameObject(this, Vec3(0, 5.25f, -3));
	ground = new GameObject(this, Vec3(0, 0, 0));
	flashLight = new GameObject(this, currentCamera->position + Vec3(0, 0, 0));
	

	light->LookAt(Vec3());
	soBright->LookAt(Vec3());
	ground->LookAt(Vec3(0, 1, 0));


	cube->addChild(soBright);
	lightAnchor->addChild(light);
	currentCamera->addChild(flashLight);

	flashLight->Rotate(Quat(20 * 3.14159f / 180.0f, Vec3::BasisX()));

	/* CREATE MODELS */
	ModelManager::getInstance()->CreateCuboid("idgaf", 0.5f, 0.5f, 0.5f);
	ModelManager::getInstance()->CreatePlane("plane", .5f, .5f);
	ModelManager::getInstance()->CreateCuboid("light", 0.25f, 0.25f, 0.25f);
	ModelManager::getInstance()->CreatePlane("ground", 100, 100);
	ModelManager::getInstance()->CreatePyramid("directional", 2.5f, 2.5f, 2.5f);

	/* CREATE TEXTURES */

	float pixelData[]
	{
		0.0f, 1.0f, 0.0f, 1.0f,		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,		0.0f, 1.0f, 0.0f, 1.0f
	};
	ModelManager::getInstance()->createTexture("greenCheckers", pixelData, 2, 2);

	float pixelDataRed[]
	{
		1.0f, 0.0f, 0.0f, 1.0f,		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,		1.0f, 0.0f, 0.0f, 1.0f
	};

	ModelManager::getInstance()->createTexture("redCheckers", pixelDataRed, 2, 2);
	ModelManager::getInstance()->loadTexture("star", "Images/star.png");
	ModelManager::getInstance()->loadTexture("smoke", "Images/Smoke.png");
	ModelManager::getInstance()->loadTexture("grass", "Images/grass.png");

	/* Add Components */
	new RenderableComponent("idgaf", "redCheckers", cube);
	new RenderableComponent("light", "star", soBright);
	new RenderableComponent("ground", "grass", ground);
	new RenderableComponent("directional", "greenCheckers", light);

	new ParticleSystem(lilCube, ParticleSystem::Emitter_Type_Sphere, "plane", "smoke", 10, 1, 5);

	new Light(light, Vec4(0, 1.0f, 1.0f, 1.0f), Light::Directional);
	new Light(soBright, Vec4(1, 8, 8, 0), Light::Spot, 90 * 3.14159f / 180.0f);

	new Light(flashLight, Vec4(1, 20, 20, 20), Light::Spot, 60 * 3.14159f / 180.0f);

	/* PUSH MODELS */
	ModelManager::getInstance()->PushModels();

	//Setup the input controller here
	BindKey(SDLK_b, BindKey(SDLK_v, new CameraUp(currentCamera, SDLK_SPACE)));
	new CameraDown(currentCamera, SDLK_x);
	new CameraRight(currentCamera, SDLK_d);
	new CameraLeft(currentCamera, SDLK_a);
	new CameraForward(currentCamera, SDLK_w);
	new CameraBackward(currentCamera, SDLK_s);
	new CameraTurnLeft(currentCamera, SDLK_q);
	new CameraTurnRight(currentCamera, SDLK_e);
	new CameraTurnDown(currentCamera, SDLK_c);
	new CameraTurnUp(currentCamera, SDLK_z);
	new CameraRollLeft(currentCamera, SDLK_r);
	new CameraRollRight(currentCamera, SDLK_f);

	new GameObject_PosX(cube, SDLK_LEFT);
	new GameObject_NegX(cube, SDLK_RIGHT);
	new GameObject_ScaleUp(cube, SDLK_UP);
	new GameObject_ScaleDown(cube, SDLK_DOWN);

	new AmbientBrightnessUp(&ambientLightColor, Game::GetInstance()->inputManager->mouseButtonDict[SDL_BUTTON_LEFT]);
	new AmbientBrightnessDown(&ambientLightColor, Game::GetInstance()->inputManager->mouseButtonDict[SDL_BUTTON_RIGHT]);
}

TestLevel::~TestLevel(){}

void TestLevel::LevelUpdate(float _timeStep)
{
	Level::LevelUpdate(_timeStep);

	cube->GetTransform().Rotate(Quat(0.6f * _timeStep, Vec3(0, 1, 0)));
	lightAnchor->GetTransform().Rotate(Quat(-0.6f * _timeStep, Vec3(1, 1, 0)));
}

void TestLevel::DebugRender()
{

}

