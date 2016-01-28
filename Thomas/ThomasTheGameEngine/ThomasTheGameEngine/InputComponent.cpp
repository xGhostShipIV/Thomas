#include "InputComponent.h"
#include "Game.h"
#include <sstream>
#include <iostream>
#include "GuiHandler.h"

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

void InputController::handleEvents(SDL_Event event_, float _timestep)
{
	MouseState = SDL_GetMouseState(&MouseX, &MouseY);

	if (event_.type == SDL_KEYDOWN)
		hitKey(event_.key.keysym.sym);
	else if (event_.type == SDL_KEYUP)
		releaseKey(event_.key.keysym.sym);
	else if (event_.type == SDL_MOUSEMOTION)
	{
		GuiHandler::getInstance()->HandleEventMouseHover(MouseX, MouseY);
		mouseMovement(event_.motion, _timestep);
	}

	//Specific handling for mouse buttons
	//Note on implementation:
	//There is a dictinoary in the InputController that maps specific mouse input to Virtual keycodes from SDL_Keycode
	//This allows mouse input to function identically to keyboard input in this particular manager.
	//The actual dictionary entries can be found in the InputController constructor

	if (event_.type == SDL_MOUSEBUTTONDOWN)
		hitKey(InputController::getInstance()->mouseButtonDict[event_.button.button]);
	else if (event_.type == SDL_MOUSEBUTTONUP)
		releaseKey(InputController::getInstance()->mouseButtonDict[event_.button.button]);


	/* GUI CHECKS */
	//Check for left button down
	if (event_.button.type == SDL_MOUSEBUTTONDOWN &&
		event_.button.button == SDL_BUTTON_LEFT &&
		SDL_BUTTON(PreviousMouseState) != SDL_BUTTON(MouseState))
	{
		GuiHandler::getInstance()->HandleEventMouseDown(MouseX, MouseY);
	}
	//Check for left button up
	if (event_.button.type == SDL_MOUSEBUTTONUP &&
		event_.button.button == SDL_BUTTON_LEFT &&
		SDL_BUTTON(PreviousMouseState) != SDL_BUTTON(MouseState))
	{
		GuiHandler::getInstance()->HandleEventMouseUp(MouseX, MouseY);
	}


	PreviousMouseState = MouseState;
	PreviousMouseX = MouseX;
	PreviousMouseY = MouseY;
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
	MoEvent = _event;

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

	//This sets up the dictionary for mouse click buttons to sdl_keycodes
	mouseButtonDict.insert(std::pair<Uint8, SDL_Keycode>(SDL_BUTTON_LEFT, SDLK_UNDERSCORE));
	mouseButtonDict.insert(std::pair<Uint8, SDL_Keycode>(SDL_BUTTON_MIDDLE, SDLK_AT));
	mouseButtonDict.insert(std::pair<Uint8, SDL_Keycode>(SDL_BUTTON_RIGHT, SDLK_HASH));
}