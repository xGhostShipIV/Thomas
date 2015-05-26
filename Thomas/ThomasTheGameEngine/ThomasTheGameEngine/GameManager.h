//Author:	Mathieu Violette
//Date:		5/26/2015(MV)
/* Holds main loop and GLUT inits */

#include "glut.h"

#ifndef _GAME_MANAGER_H_
#define _GAME_MANAGER_H_

class GameManager
{
	typedef void(*UpdateFunc)(int);
	typedef void(*RenderFunc)(void);
private:	
	GameManager();
	static GameManager* instance;
	
	UpdateFunc updateFunc;
	RenderFunc renderFunc;
public:
	static GameManager* GetInstance();
	~GameManager();
	void StartProgram(void(void) = nullptr, UpdateFunc = nullptr);

	void Update(int);
	void RenderScene();
};

#endif