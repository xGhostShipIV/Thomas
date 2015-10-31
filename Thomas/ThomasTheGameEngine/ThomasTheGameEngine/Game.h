//Author:	Mathieu Violette
//Date:		5/26/2015(MV), 6/6/2015(MV)
/* Holds main loop */

#ifndef _GAME_H_
#define _GAME_H_

#include <SDL.h>
#undef main
#include <glew.h>
#include <stdio.h>

#define GAME Game::GetInstance() 

class Level; class GameProperties; class AudioManager; class ModelManager; class InputController;

class Game
{
	friend class GameObject;

private:	
	bool isRunning;
	Uint32 lastUpdateTime, timeSincelastUpdate;

	SDL_Window* gameWindow;
	SDL_Renderer* gameRenderer;
	SDL_GLContext glcontext;

protected:	
	/* Inits GLUT Window*/
	Game();	
	static Game* instance;
public:
	GameProperties * properties;
	AudioManager * audioManager;
	ModelManager * modelManager;
	Level * currentLevel;
	InputController * inputManager;
	
	/* Returns the instance of Game */
	static Game* GetInstance()
	{
		if (instance == nullptr)
			instance = new Game();

		return instance;
	}

	~Game();
	
	/* Called to start game loop.*/
	void StartGame();

	/* Performs engine specific updates, then calls game's update function */
	void EngineUpdate(Uint32 timeStep); /* Engine's Update*/

	/* Performs engine draw calls, then calls game's render function */
	void EngineRender(); /* Engine's Render*/

	/* Does all the clean up of flagged gameObjects */
	void PostRender();

	//Functions that will be changed depending on the games specific needs
	virtual void Update(Uint32 timeStep){}
	virtual void Render(){}

	//Will load a new level into the engine & will unload the current level (if it exists)
	void LoadLevel(Level * _level);

	void setRunning(bool);
};

#endif