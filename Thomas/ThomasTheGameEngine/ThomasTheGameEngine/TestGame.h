//Author:	Mathieu Violette
//Date:		6/6/2015(MV)
//Testbed for Game Engine

#ifndef TEST_GAME_H
#define TEST_GAME_H

#include "Game.h"

class TestGame : public Game
{
public:

	TestGame();	
	~TestGame();

protected:

	/* Game Update Code Here */
	void Update(Uint32 _timestep);

	/* Game Render Code Here */
	void Render();
};

#endif