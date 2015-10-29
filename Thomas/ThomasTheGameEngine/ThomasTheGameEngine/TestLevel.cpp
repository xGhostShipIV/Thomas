//Author:	Mathieu Violette
//Date:		10/21/2015
//Example Level

#include "TestLevel.h"
#include "CameraInputTest.h"
#include "Cube.h"
#include "TestGame.h"
#include "AudioTester.h"

Cube* cube;
AudioTester * at;

#define BUFFER_OFFSET(i) ((void*)(i))

enum VAO_IDs { Triangles, NumVAOs };
enum Buffer_IDs { ArrayBuffer, NumBuffers };
enum Attrib_IDs { vPosition = 0 };

GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];

TestLevel::TestLevel(GLuint _program) : Level(_program)
{
	cube = new Cube(_program);
	at = new AudioTester();
	gameObjects.push_back(at);
	gameObjects.push_back(cube);


	glGenVertexArrays(NumVAOs, VAOs);
	glBindVertexArray(VAOs[Triangles]);

	glGenBuffers(NumBuffers, Buffers);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube->vertices), cube->vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(vPosition);

	currentCamera->transform->position = Vec3(0, 0, -2);

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
}

TestLevel::~TestLevel(){}

void TestLevel::LevelUpdate(UINT32 _timeStep)
{
	Level::LevelUpdate(_timeStep);

	cube->colour = cube->colour > 1000 ? 0 : cube->colour + 1;
	cube->transform->Rotate(Vec3(0, 0.1f, 0));
}