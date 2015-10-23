#pragma once
#include "InputComponent.h"
#include "Game.h"

class CloseGame : public InputComponent {

public:
	void whenPressed(){
		Game::GetInstance()->setRunning(false);
		printf("\nExit\n");
	}
};