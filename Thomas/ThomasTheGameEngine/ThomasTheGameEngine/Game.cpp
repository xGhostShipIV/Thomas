//Author:	Mathieu Violette
//Date:		10/22/2015

#include "Game.h"
#include "Level.h"
#include "GameObject.h"
#include "Input.h"
#include "InputComponent.h"
#include "GameProperties.h"
#include "AudioManager.h"
#include "ModelManager.h"
#include "Camera.h"
#include "OpenGLUtilities.h"

Game* Game::instance = nullptr;

Game::Game()
{
	instance = this;

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

	modelManager = ModelManager::getInstance();
};

Game::~Game()
{
	/* delete SDL stuff */
	delete audioManager;
	delete modelManager;
	delete properties;

	SDL_GL_DeleteContext(glcontext);
	SDL_DestroyRenderer(gameRenderer);
	SDL_DestroyWindow(gameWindow);
	SDL_Quit();
}

void Game::StartGame()
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
				if (evt.type == SDL_KEYDOWN)
					InputController::getInstance()->hitKey(evt.key.keysym.sym);
				//Input::PostEvent(evt);

				//If user presses close button (top right X) or Esc key: exit game loop*/
				////if (Input::Button_Pressed_Close() || Input::Keydown_ESCAPE())
				if (evt.type == SDL_QUIT)
				{
					isRunning = false;
					printf("\nExit\n");
				}
			}
			SDL_PumpEvents();

			EngineUpdate(timeSincelastUpdate);
			EngineRender();
		}
		Input::Clear();
	}
}

void Game::EngineUpdate(Uint32 _timeStep)
{
	if (currentLevel)
		currentLevel->LevelUpdate(_timeStep);

	Update(_timeStep);
}

void Game::EngineRender()
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

void Game::PostRender()
{
	if (currentLevel)
		currentLevel->LevelCleanUp();
}

void Game::LoadLevel(Level * _level)
{
	if (currentLevel)
		delete currentLevel;

	currentLevel = _level;
}

void Game::setRunning(bool _isRunning) {
	isRunning = _isRunning;
}