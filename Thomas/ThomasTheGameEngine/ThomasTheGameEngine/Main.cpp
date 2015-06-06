//Author:	Mathieu Violette
//Date:		4/9/2015(MV)
//Testbed for Game Engine

#include "Thomas.h"
#include <conio.h>
#include "TestGame.h"

int main()
{
	TestGame* testgame = TestGame::GetInstance();
	testgame->StartGame();
	delete testgame;

	_getch(); // Press any key
	return 0;
}