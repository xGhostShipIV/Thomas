//Author:	Mathieu Violette, Nathan Senter
//Date:		10/21/2015, 11/24,2015(NS)
//Example Level

#pragma once

#include <Level.h>
#include <ModelManager.h>
#include <RenderableComponent.h>
#include <Texture.h>
#include <Light.h>
#include <Billboard.h>
#include <ParticleSystem.h>

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
	GameObject* cube, *lilCube;
	RenderableComponent *cubey, *pointyLight;
	GameObject * lilCubey;
	Texture* texture;
	GameObject* light, *soBright;
	Light *directionLightOne, *directionLightTwo;

	ParticleSystem * p;

	void DebugRender() override;
	void LevelUpdate(UINT32 _timeStep) override;

};