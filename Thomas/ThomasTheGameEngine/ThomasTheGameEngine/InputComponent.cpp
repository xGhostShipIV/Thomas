#include "InputComponent.h"

InputController * InputController::instance;

InputComponent::InputComponent(GameObject * _go) : Component(_go){

}

InputComponent::~InputComponent()
{

}

void InputController::bindKey(SDL_Keycode key, InputComponent * action) {
	//inputMap[key] = action;
	inputMap.insert(std::pair<SDL_Keycode, InputComponent*>(key, action));
}

void InputController::unbindKey(SDL_Keycode key) {
	inputMap.erase(key);
}

//Research indicates that the search of the map is required to lookup by value
void InputController::unbindAction(InputComponent * action) {
	for (auto it = inputMap.begin(); it != inputMap.end(); it++) {
		if (it->second == action) {
			inputMap.erase(it->first);
		}
	}
}

void InputController::swapKeybinds(SDL_Keycode key1, SDL_Keycode key2) {
	std::pair< SDL_Keycode, InputComponent *> temp;

	temp.second = inputMap[key1];

	inputMap[key2] = inputMap[key1];

	inputMap[key1] = temp.second;	
}

void InputController::hitKey(SDL_Keycode key) {
	if (inputMap.find(key) != inputMap.end())
	inputMap.find(key)->second->whenPressed();
}