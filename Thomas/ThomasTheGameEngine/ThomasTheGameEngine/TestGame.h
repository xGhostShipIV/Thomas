//Author:	Mathieu Violette
//Date:		6/6/2015(MV)
//Testbed for Game Engine

class TestGame;

#define GAMETYPE TestGame
#include "Game.h"

#ifndef TEST_GAME_H
#define TEST_GAME_H

class TestGame : public Game<TestGame>
{
public:
	TestGame(){}
	~TestGame(){}
protected:

	/* Game Update Code Here */
	void Update(UINT32)
	{
		
	}

	/* Game Render Code Here */
	void Render()
	{
		/* Move Left 1.5 Units And Into The Screen 6.0 */
		glLoadIdentity();
		glTranslatef(-1.5f, 0.0f, -6.0f);

		glBegin(GL_TRIANGLES);            /* Drawing Using Triangles */
		glVertex3f(0.0f, 1.0f, 0.0f); /* Top */
		glVertex3f(-1.0f, -1.0f, 0.0f); /* Bottom Left */
		glVertex3f(1.0f, -1.0f, 0.0f); /* Bottom Right */
		glEnd();                           /* Finished Drawing The Triangle */

		/* Move Right 3 Units */
		glTranslatef(3.0f, 0.0f, 0.0f);

		glBegin(GL_QUADS);                /* Draw A Quad */
		glVertex3f(-1.0f, 1.0f, 0.0f); /* Top Left */
		glVertex3f(1.0f, 1.0f, 0.0f); /* Top Right */
		glVertex3f(1.0f, -1.0f, 0.0f); /* Bottom Right */
		glVertex3f(-1.0f, -1.0f, 0.0f); /* Bottom Left */
		glEnd();                           /* Done Drawing The Quad */
	}
};

#endif