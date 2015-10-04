#include "InputComponent.h"

InputController::bindKey(SDL_Keycode key, InputComponent& action) {
	inputMap[key] = action;
}

InputController::unbindKey(SDL_Keycode key) {
	inputMap.erase(key);
}

//Research indicates that the search of the map is required to lookup by value
InputController::unbindAction(InputComponent& action) {
	for (auto it = inputBoard.begin(); it != inputBoard.end(); it++) {
		if (it->second == action) {
			inputBoard.erase(it->first);
		}
	}
}

InputController::swapKeybinds(SDL_Keycode key1, SDL_Keycode key2) {
	std::pair < SDL_Keycode, InputComponent&) temp;
	temp = inputMap[key1];
	inputMap[key2] = inputMap[key1];
	inputMap[key1] = temp;	
}

InputController::hitKey(SDL_Keycode key) {
	*(inputMap.find(key))->second->whenPressed();
}


//Someone double check this
InputController::getInstance() {
	static InputController instance;
	return instance;
}