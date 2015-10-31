#pragma once
#include <InputComponent.h>
#include <Game.h>

/*
	Input to control the exiting of the game when pressing ESC
*/
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