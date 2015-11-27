#include "InputComponent.h"
#include "Game.h"

InputController * InputController::instance;

InputComponent::InputComponent(GameObject * _go, SDL_Keycode key) : Component(_go, Component::ComponentType::Input)
{
	hasBeenPressed = false;

	Game::GetInstance()->inputManager->bindKey(key, this);
}


InputComponent::~InputComponent()
{

}

InputComponent* InputController::bindKey(SDL_Keycode key, InputComponent * action) {
	inputMap.insert(std::pair<SDL_Keycode, InputComponent*>(key, action));

	return action;
}

void InputController::unbindKey(SDL_Keycode key) {
	inputMap.erase(key);
}

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

	for (auto it = keysDown.begin(); it != keysDown.end(); it++)
	{
		if ((*it) == key)
			return;
	}

	keysDown.push_back(key);
}

void InputController::releaseKey(SDL_Keycode key)
{
	for (auto it = keysDown.begin(); it != keysDown.end(); it++)
	{
		if ((*it) == key)
		{
			keysDown.erase(it);
			return;
		}
	}
}

void InputController::Update(float _timestep)
{
	int newMouseX, newMouseY;
	SDL_GetMouseState(&newMouseX, &newMouseY);

	for (auto it = keysDown.begin(); it != keysDown.end(); it++)
	{
		if (inputMap.find(*it) != inputMap.end())
		{
			if (!inputMap.find(*it)->second->hasBeenPressed) {
				inputMap.find(*it)->second->whenPressed(_timestep);
				inputMap.find(*it)->second->hasBeenPressed = true;
			}
		}
	}

	mousePos = Vec2((float)newMouseX, (float)newMouseY);

	for (auto it = keysDown.begin(); it != keysDown.end(); it++)
	{
		inputMap.find(*it)->second->hasBeenPressed = false;
	}
}

InputController::InputController() {

	//This sets up the dictionary for mouse click buttons to sdl_keycodes
	mouseButtonDict.insert(std::pair<Uint8, SDL_Keycode>(SDL_BUTTON_LEFT, SDLK_UNDERSCORE));
	mouseButtonDict.insert(std::pair<Uint8, SDL_Keycode>(SDL_BUTTON_MIDDLE, SDLK_AT));
	mouseButtonDict.insert(std::pair<Uint8, SDL_Keycode>(SDL_BUTTON_RIGHT, SDLK_HASH));

}