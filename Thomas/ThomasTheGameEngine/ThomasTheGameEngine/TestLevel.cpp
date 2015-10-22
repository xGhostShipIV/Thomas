//Author:	Mathieu Violette
//Date:		10/21/2015
//Example Level

#include "TestLevel.h"
#include "TestGame.h"
#include "CameraInputTest.h"
#include "Cube.h"
#include "Game.h"

Cube* cube;

#define BUFFER_OFFSET(i) ((void*)(i))

enum VAO_IDs { Triangles, NumVAOs };
enum Buffer_IDs { ArrayBuffer, NumBuffers };
enum Attrib_IDs { vPosition = 0 };

GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];

TestLevel::TestLevel(GLuint _program) : Level(_program)
{
	cube = new Cube(_program);
	gameObjects.push_back(cube);


	glGenVertexArrays(NumVAOs, VAOs);
	glBindVertexArray(VAOs[Triangles]);

	glGenBuffers(NumBuffers, Buffers);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube->vertices), cube->vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(vPosition);

	//Setup the input controller here
	CameraUp * cho = new CameraUp(currentCamera);
	currentCamera->addComponent(cho,cho);

	TestGame::GetInstance()->inputManager->bindKey(SDLK_w, cho);
}

TestLevel::~TestLevel(){}

void TestLevel::LevelUpdate(UINT32 _timeStep)
{
	Level::LevelUpdate(_timeStep);

	cube->colour = cube->colour > 1000 ? 0 : cube->colour + 1;
	cube->Rotation.y += 0.1f;
}