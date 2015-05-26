//Author:	Mathieu Violette
//Date:		4/9/2015(MV)
//Testbed for Game Engine

#include "Thomas.h"

void RenderScene(void);

int main()
{
	GameManager* testgame = GameManager::GetInstance();

	testgame->StartProgram(RenderScene);

	return 0;
}

void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glutSwapBuffers();
}