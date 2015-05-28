//Author:	Mathieu Violette
//Date:		4/9/2015(MV)
//Testbed for Game Engine

#include "Thomas.h"
#include <conio.h>

void RenderScene(void);
void Update(UINT32);

int main()
{
	GameManager* testgame = GameManager::GetInstance();
	testgame->StartProgram(RenderScene, Update);
	delete testgame;

	_getch(); // Press any key
	return 0;
}

/* Game Specific Rendering*/
void RenderScene()
{
	/* EXAMPLE STUFF */
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
}

/* Game Specific Updates*/
void Update(UINT32 timeStep)
{

}