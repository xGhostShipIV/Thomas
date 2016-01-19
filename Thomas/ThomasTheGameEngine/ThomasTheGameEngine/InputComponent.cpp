#include "InputComponent.h"
#include "Game.h"
#include <sstream>
#include <iostream>

InputController * InputController::instance;

InputComponent::InputComponent(GameObject * _go, SDL_Keycode key) : Component(_go, Component::ComponentType::Input)
{
	hasBeenPressed = false;

	Game::GetInstance()->inputManager->bindKey(key, this);
}

InputComponent::InputComponent(GameObject * _go, MouseMovement _event) : Component(_go, Component::ComponentType::Input)
{
	hasBeenPressed = false;

	Game::GetInstance()->inputManager->bindMouseEvent(_event, this);
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

InputComponent* InputController::bindMouseEvent(MouseMovement _movement, InputComponent * _action)
{
	motionMap.insert(std::pair<MouseMovement, InputComponent*>(_movement, _action));

	return _action;
}

void InputController::unbindMouseEvent(MouseMovement _movement) {
	motionMap.erase(_movement);
}

void InputController::unbindAction(InputComponent * action) {
	for (auto it = inputMap.begin(); it != inputMap.end(); it++) {
		if (it->second == action) {
			inputMap.erase(it->first);
		}
	}

	for (auto it = motionMap.begin(); it != motionMap.end(); it++) {
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

void InputController::mouseMovement(SDL_MouseMotionEvent _event, float _timestep)
{
	//Find out what type of event it is
	Vec2 _motion = Vec2(_event.xrel, _event.yrel);
	MouseMovement _movementTypeY = MouseMovement::None;
	MouseMovement _movementTypeX = MouseMovement::None;

	if (_motion.y > 0)
		_movementTypeY = MouseMovement::Positive_Y;
	else if (_motion.y < 0)
		_movementTypeY = MouseMovement::Negative_Y;

	if (_motion.x > 0)
		_movementTypeX = MouseMovement::Positive_X;
	else if (_motion.x < 0)
		_movementTypeX = MouseMovement::Negative_X;


	for (auto it = motionMap.begin(); it != motionMap.end(); it++)
	{
		if (it->first == _movementTypeY)
		{
			if (!it->second->hasBeenPressed)
			{
				it->second->whenPressed(abs(_motion.y) * _timestep);
				it->second->hasBeenPressed = true;
			}
		}
		else if (it->first == _movementTypeX)
		{
			if (!it->second->hasBeenPressed)
			{
				it->second->whenPressed(abs(_motion.x) * _timestep);
				it->second->hasBeenPressed = true;
			}
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
		if (inputMap.find(*it) != inputMap.end())
		{
			inputMap.find(*it)->second->hasBeenPressed = false;
		}		
	}

	for (auto it = motionMap.begin(); it != motionMap.end(); it++)
	{
		if (it->second->hasBeenPressed)
		{
			it->second->hasBeenPressed = false;
		}
	}
}

InputController::InputController() {

	mousePos = Vec2(-1, -1);

	//This sets up the dictionary for mouse click buttons to sdl_keycodes
	mouseButtonDict.insert(std::pair<Uint8, SDL_Keycode>(SDL_BUTTON_LEFT, SDLK_UNDERSCORE));
	mouseButtonDict.insert(std::pair<Uint8, SDL_Keycode>(SDL_BUTTON_MIDDLE, SDLK_AT));
	mouseButtonDict.insert(std::pair<Uint8, SDL_Keycode>(SDL_BUTTON_RIGHT, SDLK_HASH));
}