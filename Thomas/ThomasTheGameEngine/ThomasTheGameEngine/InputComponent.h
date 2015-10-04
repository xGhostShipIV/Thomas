#pragma once

#include "Component.h"
#include <map>
#include "dependencies\SDL\include\SDL.h"

class InputComponent : Component {
public:
	void whenPressed() = 0;
};

class InputController{
public:
	static InputController& getInstance();
	void bindKey(SDL_Keycode, InputComponent&);
	void unbindKey(SDL_Keycode);
	void unbindAction(InputComponent&);
	void swapKeybinds(SDL_Keycode, SDL_Keycode);

	void hitKey(SDL_Keycode);

private:
	InputController();
	~InputController();
	std::map<SDL_Keycode, InputComponent*> inputMap;
}