#pragma once
#include <InputComponent.h>
#include <Game.h>

/*
	Input to control the exiting of the game when pressing ESC
*/
class CloseGame : public InputComponent {

public:
	CloseGame(GameObject * _go, SDL_Keycode key) : InputComponent(_go, key)
	{

	}
	~CloseGame(){}

	void whenPressed(float _timestep){
		Game::GetInstance()->setRunning(false);
		printf("\nExit\n");
	}
};