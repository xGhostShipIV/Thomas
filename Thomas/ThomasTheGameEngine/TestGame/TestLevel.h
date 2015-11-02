//Author:	Mathieu Violette
//Date:		10/21/2015
//Example Level

#pragma once

#include <Level.h>
#include <ModelManager.h>
#include <RenderableComponent.h>

#include "TestGame.h"
#include "AudioTester.h"
#include "CameraInputTest.h"
#include "GameObjectInputTest.h"

/*
	A class that inherits from Level so the user can specify the behaviour of
	their game and create their own gameObjects
*/

class TestLevel : public Level
{
public:
	TestLevel();
	~TestLevel();

	AudioTester * at;
	GameObject cube, lilCube;
	RenderableComponent *cubey, *lilCubey;

	void DebugRender() override;
	void LevelUpdate(UINT32 _timeStep) override;
};