//Author:	Mathieu Violette
//Date:		10/21/2015
//Example Level

#include "TestLevel.h"
#include "AudioTester.h"
#include "CameraInputTest.h"
#include "GameObjectInputTest.h"
#include "FPS_Inputs.h"
#include <SDL.h>
#include <sstream>
#include <Flipbook.h>

#define BUFFER_OFFSET(i) ((void*)(i))

enum VAO_IDs { Triangles, NumVAOs };
enum Buffer_IDs { ArrayBuffer, NumBuffers };
enum Attrib_IDs { vPosition = 0 };

GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];

TestLevel::TestLevel()
{
	currentCamera->position = Vec3(0, 3, -8);

	ambientLightColor = Colour(0.1f, 0.1f, 0.1f);

	new AudioTester(this);

	cube = new GameObject(this, Vec3(0, 0.5f, 0));
	lilCube = new GameObject(this, Vec3(2, 0.5f, 0));
	light = new GameObject(this, Vec3(0, 30, 40));
	lightAnchor = new GameObject(this, Vec3());
	soBright = new GameObject(this, Vec3(0, 5.25f, -3));
	ground = new GameObject(this, Vec3(0, 0, 0));
	flashLight = new GameObject(this, currentCamera->position + Vec3(0, 1, -1));
	skybox = new GameObject(this, currentCamera->position);
	//teddy = new GameObject(this, Vec3(2, -10, 2));
	bear = new GameObject(this, Vec3(-3, 0, 2));
	lilbear = new GameObject(this, Vec3(-4.5f, 0, 2));
	InsideCube = new GameObject(this, Vec3(12, 5.1f, 0));
	OutsideCube = new GameObject(this, InsideCube->position);
	//animationGuy = new Billboard(this, Vec3(4, 4, 4));

	FontManager::getInstance()->GenerateFont("font", 72, "Font/DroidSans.ttf");
	FontManager::getInstance()->GenerateFont("lazyfont", 50, "Font/ostrich-black.ttf");

	Label *label2 = new Label(this, "HELLO WORLD", Vec2(0, 0.9f), FontManager::getInstance()->GetFont("font"), Colour::Blue());
	label = new Label(this, "WOW!", Vec2(-0.8f, -0.8f), FontManager::getInstance()->GetFont("lazyfont"), Colour::Pink());
	fpsLabel = new Label(this, "MUCH LABELS!", Vec2(0.68f, -0.68f), FontManager::getInstance()->GetFont("lazyfont"), Colour::Lime());
	fpsLabel->Rotate(Quat(45 * 3.141592654f / 180.0f, Vec3::BasisZ()));

	light->LookAt(Vec3());
	soBright->LookAt(Vec3());
	ground->LookAt(Vec3(0, 1, 0));
	flashLight->LookAt(Vec3(0, 1, 0));

	cube->addChild(soBright);
	lightAnchor->addChild(light);
	currentCamera->addChild(flashLight);
	InsideCube->addChild(OutsideCube);


	flashLight->Rotate(Quat(20 * 3.14159f / 180.0f, Vec3::BasisX()));
	//teddy->Scale(Vec3::One() * 0.1f);
	//teddy->Rotate(Quat(3.14159f, Vec3::BasisY()));
	bear->Scale(Vec3::One() * 0.2f);
	bear->Rotate(Quat(3.14159f, Vec3::BasisY()));
	lilbear->Scale(Vec3::One() * 0.1f);
	lilbear->Rotate(Quat(150 * 3.14159f / 180.0f, Vec3::BasisY()));

	/* CREATE MODELS */
	ModelManager::getInstance()->loadModel("teddy", "Models/teddy.obj", false, ModelManager::Draw_Mode::CW);
	ModelManager::getInstance()->loadModel("bear", "Models/bear-obj.obj", true, ModelManager::Draw_Mode::CW);
	ModelManager::getInstance()->loadModel("torch", "Models/torch.obj", true);
	ModelManager::getInstance()->CreateCuboid("cube", 0.5f, 0.5f, 0.5f, true);
	ModelManager::getInstance()->CreateCuboid("InCubeO", 5, 5, 5, true);
	ModelManager::getInstance()->CreateSkybox("InCubeI", 5, false);
	ModelManager::getInstance()->CreatePlane("plane", .5f, .5f);
	ModelManager::getInstance()->CreateCuboid("light", 0.25f, 0.25f, 0.25f);
	ModelManager::getInstance()->CreatePlane("ground", 100, 100, 32, 32);
	ModelManager::getInstance()->CreatePyramid("directional", 2.5f, 2.5f, 2.5f);
	ModelManager::getInstance()->CreateSkybox("skybox", 200);

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
	ModelManager::getInstance()->loadTexture("skybox", "Images/Day_Skybox.png");
	ModelManager::getInstance()->loadTexture("bear", "Images/bear.tif");
	ModelManager::getInstance()->loadTexture("bearTeeth", "Images/bear_teeth_transparent.tif");
	//ModelManager::getInstance()->loadTexture("teddyFur", "Images/brown-fur-texture.png");
	ModelManager::getInstance()->loadTexture("dice", "Images/dice_texture.png");
	ModelManager::getInstance()->loadTexture("torchTexture", "Images/torch_DIF.tif");

	/* Add Components */
	new RenderableComponent("cube", "dice", cube);
	new RenderableComponent("light", "star", soBright);
	new RenderableComponent("ground", "grass", ground);
	new RenderableComponent("directional", "greenCheckers", light);
	new RenderableComponent("skybox", "skybox", skybox);
	//new RenderableComponent("teddy", "teddyFur", teddy);
	//new RenderableComponent("torch", "torchTexture", teddy);

	new RenderableComponent("InCubeO", "dice", OutsideCube);
	RenderableComponent *inRC = new RenderableComponent("InCubeI", "dice", InsideCube);
	inRC->SetEffecctedByLight(false, true, true);

	RenderableComponent *bearRC = new RenderableComponent("bear", "bear", bear);
	bearRC->textureName.push_back(ModelManager::getInstance()->GetTextureID("bearTeeth"));
	bearRC->textureName.push_back(ModelManager::getInstance()->GetTextureID("bearTeeth"));

	RenderableComponent *lilbearRC = new RenderableComponent("bear", "bear", lilbear);
	lilbearRC->textureName.push_back(ModelManager::getInstance()->GetTextureID("bearTeeth"));
	lilbearRC->textureName.push_back(ModelManager::getInstance()->GetTextureID("bearTeeth"));

	new ParticleSystem(lilCube, ParticleSystem::Emitter_Type_Sphere, "plane", "smoke", 10, 1, 5);

	new Light(light, Colour(1.0f, 1.0f, 1.0f), Light::Directional);
	new Light(soBright, Colour(80, 80, 0), Light::Spot, 120 * 3.14159f / 180.0f);

	new Light(flashLight, Colour(200, 200, 200), Light::Spot, 60 * 3.14159f / 180.0f);

	/*Flipbook * fb = new Flipbook(animationGuy, 16, "Images/Animation/Fire/slice0.png", 1.5f, true, Flipbook::PNG);
	fb->Play();*/

	torch = new Torch(this, Vec3(10, -5, -8));
	torch->Rotate(Quat(180 * 3.14159f / 180.0f, Vec3::BasisY()));

	/* PUSH MODELS */
	ModelManager::getInstance()->PushModels();

	/* Space Controls */
	/*BindKey(SDLK_b, BindKey(SDLK_v, new CameraUp(currentCamera, SDLK_SPACE)));
	new CameraDown(currentCamera, SDLK_x);
	
	new CameraForward(currentCamera, SDLK_w);
	new CameraBackward(currentCamera, SDLK_s);

	new CameraTurnLeft(currentCamera, SDLK_a);
	new CameraTurnRight(currentCamera, SDLK_d);
	
	new CameraTurnDown(currentCamera, SDLK_c);
	new CameraTurnUp(currentCamera, SDLK_z);
	
	new CameraRollLeft(currentCamera, SDLK_q);
	new CameraRollRight(currentCamera, SDLK_e);

	new CameraTurnRight(currentCamera, SDLK_RIGHT);
	new CameraTurnLeft(currentCamera, SDLK_LEFT);*/

	new AmbientBrightnessUp(&ambientLightColor, Game::GetInstance()->inputManager->mouseButtonDict[SDL_BUTTON_LEFT]);
	new AmbientBrightnessDown(&ambientLightColor, Game::GetInstance()->inputManager->mouseButtonDict[SDL_BUTTON_RIGHT]);

	/* FPS CONTROLS */
	SDL_SetRelativeMouseMode(SDL_TRUE); //Traps Mouse in Window (centre)
	new FPS_FORWARD(currentCamera, SDLK_w);
	new FPS_BACKWARD(currentCamera, SDLK_s);
	new FPS_STRAFE_LEFT(currentCamera, SDLK_a);
	new FPS_STRAFE_RIGHT(currentCamera, SDLK_d);

	new FPS_TURN_LEFT(currentCamera, MouseMovement::Negative_X);
	new FPS_TURN_RIGHT(currentCamera, MouseMovement::Positive_X);
	new FPS_TURN_UP(currentCamera, MouseMovement::Positive_Y);
	new FPS_TURN_DOWN(currentCamera, MouseMovement::Negative_Y);
}

TestLevel::~TestLevel()
{
}

void TestLevel::LevelUpdate(float _timeStep)
{
	Level::LevelUpdate(_timeStep);

	cube->GetTransform().Rotate(Quat(0.6f * _timeStep, Vec3(0, 1, 0)));
	lightAnchor->GetTransform().Rotate(Quat(-0.6f * _timeStep, Vec3(1, 1, 0)));
	light->LookAt(Vec3());

	//LOL
	label->Rotate(Quat(90 * 3.141592654f / 180.0f * _timeStep, Vec3::BasisZ()));
	
	/*std::stringstream ss;
	ss << "FPS: " << Game::GetInstance()->GetFPS();
	fpsLabel->SetText(ss.str());*/

	skybox->position = currentCamera->position;
}

void TestLevel::DebugRender()
{

}

