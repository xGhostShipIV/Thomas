//Author:	Mathieu Violette
//Date:		10/21/2015
//Example Level

#pragma once

#include <Level.h>
#include "CameraInputTest.h"
#include "TestGame.h"
#include "AudioTester.h"
#include <ModelManager.h>
#include <RenderableComponent.h>

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
	GameObject cube;
	RenderableComponent* cubey;

	void DebugRender() override;
	void LevelUpdate(UINT32 _timeStep) override;
};