#pragma once
#include "InputComponent.h"
#include "Game.h"

class CloseGame : public InputComponent {

public:
	CloseGame(GameObject * _go) : InputComponent(_go)
	{

	}
	~CloseGame(){}

	void whenPressed(){
		Game::GetInstance()->setRunning(false);
		printf("\nExit\n");
	}
};