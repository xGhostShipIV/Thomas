//Author:	Mathieu Violette
//Date:		4/9/2015(MV)
//Testbed for Game Engine

#include "Thomas.h"

void RenderScene(void);
void Update(int);

int main()
{
	GameManager* testgame = GameManager::GetInstance();
	testgame->StartProgram(RenderScene, Update);
	delete testgame;

	return 0;
}

void RenderScene()
{
	
}

void Update(int ID)
{

}