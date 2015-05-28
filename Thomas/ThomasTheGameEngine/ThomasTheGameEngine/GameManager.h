//Author:	Mathieu Violette
//Date:		5/26/2015(MV)
/* Holds main loop and GLUT inits */

#include "freeglut.h"

#ifndef _GAME_MANAGER_H_
#define _GAME_MANAGER_H_

class GameManager
{
	/* defines the type of functions that can be passed */
	typedef void(*UpdateFunc)(UINT32);
	typedef void(*RenderFunc)(void);

private:	
	GameManager();
	static GameManager* instance;
	bool isRunning;
	UINT32 lastUpdateTime, timeSincelastUpdate;

	UpdateFunc updateFunc;
	RenderFunc renderFunc;
public:
	static GameManager* GetInstance();
	~GameManager();

	/* takes in 2 function pointer for the game's render and update*/
	void StartProgram(RenderFunc = nullptr, UpdateFunc = nullptr);

	void Update(UINT32);
	void RenderScene();
};

#endif