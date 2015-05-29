//Author:	Mathieu Violette
//Date:		5/26/2015(MV)

#include <SDL.h>
#undef main

#include <glew.h>
#include "GameManager.h"
#include <stdio.h>

GameManager* GameManager::instance = nullptr;

SDL_Window* gameWindow;
SDL_Renderer* gameRenderer;
SDL_GLContext glcontext;

//Declare Update function
//void Update(int ID);


/* Returns the instance of GameManager */
GameManager* GameManager::GetInstance()
{
	if (instance == nullptr)
		instance = new GameManager();
	
	return instance;
}

/* Inits GLUT Window*/
GameManager::GameManager()
{
	int width, height;
	width = 1024;
	height = 768;

	/* Game Loop Flag */
	isRunning = true;
	lastUpdateTime = 0, timeSincelastUpdate = 0;

	//Game's function pointers
	updateFunc = nullptr;
	renderFunc = nullptr;

	///SDL stuff
	SDL_Init(SDL_INIT_VIDEO);
	SDL_RendererInfo displayRendererInfo;
	SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_OPENGL, &gameWindow, &gameRenderer);

	SDL_GetRendererInfo(gameRenderer, &displayRendererInfo);
	if ((displayRendererInfo.flags & SDL_RENDERER_ACCELERATED) == 0 ||
		(displayRendererInfo.flags & SDL_RENDERER_TARGETTEXTURE) == 0) {
		/* We have no render surface and not accelerated. */
		printf("\n NO RENDER SURFACE \n");
	}

	/* creates a context for OpenGL draw calls */
	glcontext = SDL_GL_CreateContext(gameWindow);

	//OpenGL stuff  (can change later)
	{
		/* Enable smooth shading */
		glShadeModel(GL_SMOOTH);

		/* Set the background black */
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

		/* Depth buffer setup */
		glClearDepth(1.0f);

		/* Enables Depth Testing */
		glEnable(GL_DEPTH_TEST);

		/* The Type Of Depth Test To Do */
		glDepthFunc(GL_LEQUAL);

		/* Really Nice Perspective Calculations */
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	
		/* Height / width ration */
		GLfloat ratio;
		ratio = (GLfloat)width / (GLfloat)height;

		/* Setup our viewport. */
		glViewport(0, 0, (GLsizei)width, (GLsizei)height);

		/* change to the projection matrix and set our viewing volume. */
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		/* Set our perspective */
		gluPerspective(45.0f, ratio, 0.1f, 100.0f);

		/* Make sure we're chaning the model view and not the projection */
		glMatrixMode(GL_MODELVIEW);

		/* Reset The View */
		glLoadIdentity();
	}

}

GameManager::~GameManager()
{
	/* delete SDL stuff */
	SDL_GL_DeleteContext(glcontext);
	SDL_DestroyRenderer(gameRenderer);
	SDL_DestroyWindow(gameWindow);
	SDL_Quit();
}

/* Called to start game loop.*/
void GameManager::StartProgram(RenderFunc render, UpdateFunc update)
{
	updateFunc = update;
	renderFunc = render;
	
	//Event Handling
	SDL_Event evt;

	/* Game Loop */
	while (isRunning)
	{	
		timeSincelastUpdate = SDL_GetTicks() - lastUpdateTime;
		if (timeSincelastUpdate >= 16)
		{

			while (SDL_PollEvent(&evt))
			{
				/* If user presses top right X or Esc key: exit game loop*/
				if (evt.type == SDL_QUIT || evt.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
				{
					isRunning = false;
					printf("\nExit\n");
				}
				//Event Manager
				//Game::eventManager.ManageEvents(&evt);
			}
			SDL_PumpEvents();

			Update(timeSincelastUpdate);
			RenderScene();
		}
	}
}

/* Performs engine draw calls, then calls game's render function */
void GameManager::RenderScene() /* Engine's Render*/
{
	/* Set the background */
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	/* Clear The Screen And The Depth Buffer */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Game's Render Call
	if (renderFunc != nullptr)
		renderFunc();

	for (int i = 0; i < gameObjects.size(); i++)
	{
		if (!gameObjects[i]->isFlagged) 
			gameObjects[i]->Render();
		else
			gameObjectsToBeDeleted.push_back(gameObjects[i]);
	}

	/* Render to screen */
	SDL_GL_SwapWindow(gameWindow);
	SDL_RenderPresent(gameRenderer);

	PostRender();
}

/* Does all the clean up of flagged gameObjects */
void GameManager::PostRender()
{
	for (auto it = gameObjectsToBeDeleted.begin(); it != gameObjectsToBeDeleted.end(); it++)
	{
		gameObjects.erase(it);

		delete it._Ptr;
	}
}

/* Performs engine specific updates, then calls game's update function */
void GameManager::Update(UINT32 timeStep) /* Engine's Update*/
{
		
	for (int i = 0; i < gameObjects.size(); i++)
	{
		if (!gameObjects[i]->isFlagged)
			gameObjects[i]->Update(timeStep);
	}

	//Game's Update Call
	if (updateFunc != nullptr)
		updateFunc(timeStep);
}