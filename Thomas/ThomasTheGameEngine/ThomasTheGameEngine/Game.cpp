//Author:	Mathieu Violette
//Date:		10/22/2015

#include "Game.h"
#include "Level.h"
#include "GameObject.h"
#include "InputComponent.h"
#include "GameProperties.h"
#include "AudioManager.h"
#include "ModelManager.h"
#include "Camera.h"
#include "OpenGLUtilities.h"
#include "FontManager.h"

Game* Game::instance = nullptr;

int timeStart, timeSinceLastFPSUpdate, timeSinceLastUpdate, updatesCount;
float deltaTime;
float FPS_CAP;

Game::Game()
{
	instance = this;

	/* Game Loop Flag */
	isRunning = true;
	lastUpdateTime = 0, timeSincelastUpdate = 0;

	///SDL stuff
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF);
	TTF_Init();
	Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG);

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

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glCullFace(GL_FRONT);
	glDepthFunc(GL_LESS);
	glDepthMask(GL_TRUE);
	glFrontFace(GL_CCW);


	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	modelManager = ModelManager::getInstance();

	currentLevel = nullptr;

	/* Get Moniter Refresh Rate */
	SDL_DisplayMode target, moniter;
	target.w = properties->getVideoProperties()->screenWidth;
	target.h = properties->getVideoProperties()->screenHeight;
	target.format = 0;  // don't care
	target.refresh_rate = 0; // don't care
	target.driverdata = 0; // initialize to 0
	SDL_GetClosestDisplayMode(0, &target, &moniter);
	FPS_CAP = moniter.refresh_rate;

	//FPS
	{
		timeSinceLastUpdate = timeStart = glutGet(GLUT_ELAPSED_TIME);
		updatesCount = 0;
		timeSinceLastFPSUpdate = timeStart;
		FPS = 0;
	}
};

Game::~Game()
{
	/* delete managers */
	delete FontManager::getInstance();

	/* delete SDL stuff */
	delete audioManager;
	delete modelManager;
	delete properties;

	SDL_GL_DeleteContext(glcontext);
	SDL_DestroyRenderer(gameRenderer);
	SDL_DestroyWindow(gameWindow);

	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void Game::StartGame()
{
	//Event Handling
	SDL_Event evt;

	Uint32 timeSinceLastRender = 0;

	/* Game Loop */
	while (isRunning)
	{
		timeSincelastUpdate = SDL_GetTicks() - lastUpdateTime;
		//if (timeSincelastUpdate >= 1000 / 1000.0f)
		{
			lastUpdateTime = SDL_GetTicks();

			while (SDL_PollEvent(&evt))
			{
				if (evt.type == SDL_KEYDOWN)
					InputController::getInstance()->hitKey(evt.key.keysym.sym);
				else if (evt.type == SDL_KEYUP)
					InputController::getInstance()->releaseKey(evt.key.keysym.sym);
				else if (evt.type == SDL_MOUSEMOTION)
					InputController::getInstance()->mouseMovement(evt.motion, timeSincelastUpdate / 1000.0f);

				//Specific handling for mouse buttons
				//Note on implementation:
				//There is a dictinoary in the InputController that maps specific mouse input to Virtual keycodes from SDL_Keycode
				//This allows mouse input to function identically to keyboard input in this particular manager.
				//The actual dictionary entries can be found in the InputController constructor

				if (evt.type == SDL_MOUSEBUTTONDOWN)
					InputController::getInstance()->hitKey(InputController::getInstance()->mouseButtonDict[evt.button.button]);
				else if (evt.type == SDL_MOUSEBUTTONUP)
					InputController::getInstance()->releaseKey(InputController::getInstance()->mouseButtonDict[evt.button.button]);

				if (evt.type == SDL_QUIT)
				{
					isRunning = false;
					printf("\nExit\n");
				}
			}
			SDL_PumpEvents();

			EngineUpdate(timeSincelastUpdate / 1000.0f);

			timeSinceLastRender += timeSincelastUpdate;

			//if (timeSinceLastRender >= 1000 / FPS_CAP)
			{
				timeSinceLastRender = 0;
				EngineRender();
			}
			
		}		
	}
}

void Game::EngineUpdate(float _timeStep)
{
	InputController::getInstance()->Update(_timeStep);

	if (currentLevel)
		currentLevel->LevelUpdate(_timeStep);

	Update(_timeStep);
}



void Game::EngineRender()
{
	//FPS
	{
		int updateTime = glutGet(GLUT_ELAPSED_TIME);
		timeSinceLastUpdate = updateTime;
		updatesCount++;

		if (updatesCount >= 10)
		{
			FPS = updatesCount / ((float)(updateTime - timeSinceLastFPSUpdate) / 1000.f);
			timeSinceLastFPSUpdate = updateTime;
			updatesCount = 0;
		}
	}

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
	SDL_GL_SwapWindow(gameWindow);

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

float Game::GetFPS()
{
	return FPS;
}