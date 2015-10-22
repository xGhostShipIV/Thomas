#include "closeGameInput.h"

void CloseGame::whenPressed(){
	Game<GAMETYPE>::GetInstance()->setRunning(false);
}