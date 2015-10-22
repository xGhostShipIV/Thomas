//Author:	Mathieu Violette
//Date:		5/26/2015(MV), 6/6/2015(MV)
/* Holds main loop */

#ifndef _GAME_H_
#define _GAME_H_

#include <SDL.h>
#undef main
#include <glew.h>
#include <stdio.h>
#include "OpenGLUtilities.h"
#include "GameObject.h"
#include "Input.h"
#include "InputComponent.h"
#include "GameProperties.h"

#include "Level.h"
#include "AudioManager.h"

#include "Camera.h"

#define GAME Game<>::GetInstance() 

class DefaultGame;
#define GAMETYPE DefaultGame

template<class T = GAMETYPE>
class Game
{
	friend class GameObject;

private:
	
	bool isRunning;
	UINT32 lastUpdateTime, timeSincelastUpdate;

	SDL_Window* gameWindow;
	SDL_Renderer* gameRenderer;
	SDL_GLContext glcontext;

protected:	
	/* Inits GLUT Window*/
	Game();
	GLuint program;
	static T* instance;
public:
	GameProperties * properties;
	AudioManager * audioManager;
	Level * currentLevel;
	InputController * inputManager;
	

	/* Returns the instance of Game */
	static T* GetInstance()
	{
		if (instance == nullptr)
			instance = new T();

		//static T* instance;

		return instance;
	}

	~Game();
	
	/* Called to start game loop.*/
	void StartGame();

	/* Performs engine specific updates, then calls game's update function */
	void EngineUpdate(UINT32 timeStep); /* Engine's Update*/

	/* Performs engine draw calls, then calls game's render function */
	void EngineRender(); /* Engine's Render*/

	/* Does all the clean up of flagged gameObjects */
	void PostRender();

	//Abstract functions that will be changed depending on the games specific needs
	virtual void Update(UINT32 timeStep) = 0;
	virtual void Render() = 0;

	//Will load a new level into the engine & will unload the current level (if it exists)
	void LoadLevel(Level * _level);

	void setRunning(bool);
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

template<class T = GAMETYPE>
Game<T>::Game()
{
	/* Game Loop Flag */
	isRunning = true;
	lastUpdateTime = 0, timeSincelastUpdate = 0;

	///SDL stuff
	SDL_Init(SDL_INIT_VIDEO);

	//Creates the audio manager which additionally initializes SDL audio
	audioManager = AudioManager::getInstance();
	properties = GameProperties::getInstance();

	SDL_RendererInfo displayRendererInfo;
	SDL_CreateWindowAndRenderer(properties->getVideoProperties()->screenWidth, properties->getVideoProperties()->screenHeight,
						SDL_WINDOW_OPENGL, &gameWindow, &gameRenderer);

	if (properties->getVideoProperties()->isFullscreen) SDL_SetWindowFullscreen(gameWindow, SDL_WINDOW_FULLSCREEN);

	SDL_GetRendererInfo(gameRenderer, &displayRendererInfo);

	if ((displayRendererInfo.flags & SDL_RENDERER_ACCELERATED) == 0 ||
		(displayRendererInfo.flags & SDL_RENDERER_TARGETTEXTURE) == 0) {
		/* We have no render surface and not accelerated. */
		printf("\n NO RENDER SURFACE \n");
	}

	/* creates a context for OpenGL draw calls */
	glcontext = SDL_GL_CreateContext(gameWindow);

	if (glewInit())
	{
		//Unable to initialize GLEW ... exiting
		exit(EXIT_FAILURE);
	}
};

template<class T = GAMETYPE>
Game<T>::~Game()
{
	/* delete SDL stuff */
	delete audioManager;

	delete properties;

	SDL_GL_DeleteContext(glcontext);
	SDL_DestroyRenderer(gameRenderer);
	SDL_DestroyWindow(gameWindow);
	SDL_Quit();
}

template<class T = GAMETYPE>
void Game<T>::StartGame()
{
	//Event Handling
	SDL_Event evt;

	/* Game Loop */
	while (isRunning)
	{
		timeSincelastUpdate = SDL_GetTicks() - lastUpdateTime;
		if (timeSincelastUpdate >= 1000 / 24)
		{
			lastUpdateTime = SDL_GetTicks();

			while (SDL_PollEvent(&evt))
			{
				if(evt.type == SDL_KEYDOWN)
				InputController::getInstance()->hitKey(evt.key.keysym.sym);
				//Input::PostEvent(evt);
			}
			SDL_PumpEvents();

			/* If user presses close button (top right X) or Esc key: exit game loop*/
			/*if (Input::Button_Pressed_Close() || Input::Keydown_ESCAPE())
			{
				isRunning = false;
				printf("\nExit\n");
			}*/

			EngineUpdate(timeSincelastUpdate);
			EngineRender();
		}
		Input::Clear();
	}
}

template<class T = GAMETYPE>
void Game<T>::EngineUpdate(UINT32 _timeStep)
{
	if (currentLevel)
		currentLevel->LevelUpdate(_timeStep);

	Update(_timeStep);
}

template<class T = GAMETYPE>
void Game<T>::EngineRender()
{
	/* Set the background */
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	/* Clear The Screen And The Depth Buffer */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Call the update for the current level
	if (currentLevel)
		currentLevel->LevelRender();

	//Call the game specific Render function
	Render();

	/* Render to screen */
	SDL_RenderPresent(gameRenderer);
	SDL_GL_SwapWindow(gameWindow);
	

	//glFlush();

	PostRender();
}

template<class T = GAMETYPE>
void Game<T>::PostRender()
{
	if (currentLevel)
		currentLevel->LevelCleanUp();
}

template<class T = GAMETYPE>
void Game<T>::LoadLevel(Level * _level)
{
	if (currentLevel)
		delete currentLevel;

	currentLevel = _level;
}

template<class T = GAMETYPE>
void Game<T>::setRunning(bool _isRunning) {
	isRunning = _isRunning;
}

#endif