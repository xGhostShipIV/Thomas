//Author:	Mathieu Violette
//Date:		5/26/2015(MV), 6/6/2015(MV)
/* Holds main loop */

#ifndef _GAME_H_
#define _GAME_H_

#include <SDL.h>
#undef main
#include <glew.h>
#include <stdio.h>
//#include "freeglut.h"
#include "GameObject.h"
#include <typeinfo>

#define GAME Game<>::GetInstance() 

class DefaultGame;
#define GAMETYPE DefaultGame

template<class T = GAMETYPE>
class Game
{
	/* defines the type of functions that can be passed */
	typedef void(*UpdateFunc)(UINT32);
	typedef void(*RenderFunc)(void);

	friend class GameObject;

private:
	static T* instance;
	bool isRunning;
	UINT32 lastUpdateTime, timeSincelastUpdate;

	SDL_Window* gameWindow;
	SDL_Renderer* gameRenderer;
	SDL_GLContext glcontext;
protected:	
	/* Inits GLUT Window*/
	Game()
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

	//Lists that call all updates/renders for gameObjects in the game
	//As well as a list that will collect all flagged gameObjects and delete them
	std::vector<GameObject *> gameObjects;
	std::vector<GameObject *> gameObjectsToBeDeleted;

	UpdateFunc updateFunc;
	RenderFunc renderFunc;
public:
	//static T* GetInstance();
	/* Returns the instance of Game */
	static T* GetInstance()
	{
		if (instance == nullptr)
			instance = new T();

		return instance;
	}

	~Game()
	{
		/* delete SDL stuff */
		SDL_GL_DeleteContext(glcontext);
		SDL_DestroyRenderer(gameRenderer);
		SDL_DestroyWindow(gameWindow);
		SDL_Quit();
	}

	/* takes in 2 function pointer for the game's render and update*/
	void StartProgram(RenderFunc = nullptr, UpdateFunc = nullptr)
	{
		updateFunc = update;
		renderFunc = render;

		StartGame();
	}
	
	/* Called to start game loop.*/
	void StartGame()
	{
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

				EngineUpdate(timeSincelastUpdate);
				EngineRender();
			}
		}
	}

	/* Performs engine specific updates, then calls game's update function */
	void EngineUpdate(UINT32 timeStep) /* Engine's Update*/
	{

		for (int i = 0; i < gameObjects.size(); i++)
		{
			if (!gameObjects[i]->isFlagged)
				gameObjects[i]->Update(timeStep);
		}

		//Game's Update Call
		if (updateFunc != nullptr)
			updateFunc(timeStep);

		Update(timeStep);
	}

	/* Performs engine draw calls, then calls game's render function */
	void EngineRender() /* Engine's Render*/
	{
		/* Set the background */
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		/* Clear The Screen And The Depth Buffer */
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Game's Render Call
		if (renderFunc != nullptr)
			renderFunc();
		Render();

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
	void PostRender()
	{
		for (auto it = gameObjectsToBeDeleted.begin(); it != gameObjectsToBeDeleted.end(); it++)
		{
			gameObjects.erase(it);

			delete it._Ptr;
		}
		gameObjectsToBeDeleted.clear();
	}

	virtual void Update(UINT32 timeStep) = 0;
	virtual void Render() = 0;
};

template<class T>
T* Game<T>::instance = nullptr;

class DefaultGame : public Game<DefaultGame>
{
public:
	DefaultGame(){}
	~DefaultGame(){}
	void Update(UINT32 t){}
	void Render(){}
};

#endif