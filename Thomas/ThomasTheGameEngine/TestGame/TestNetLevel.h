//Author:	Mathieu Violette
//Date:		1/18/2015

#pragma once

#include <Level.h>
#include <ModelManager.h>
#include <RenderableComponent.h>
#include <Texture.h>
#include <Light.h>
#include <Billboard.h>
#include <ParticleSystem.h>
#include <Label.h>
#include <FontManager.h>
#include <Flipbook.h>
#include <GuiImage.h>

#include "TestGame.h"

/*
A class that inherits from Level so the user can specify the behaviour of
their game and create their own gameObjects
*/

class TestNetLevel : public Level
{
public:
	union SDLEventxfer
	{
		SDL_Event e;
		char c[sizeof(SDL_Event)];
	};

	TestNetLevel();
	~TestNetLevel();

	GameObject *skybox, *ground, *Frosty, *frosty_face, *frosty_nose;
	GameObject *light;

	IPaddress serverIP, *clientIP;
	TCPsocket serverSocket, clientSocket;
	int quit, len;
	char buffer[512];
	bool connected, isServer;

	void DebugRender() override;
	void LevelUpdate(float _timeStep) override;

   //possible thread needed
};