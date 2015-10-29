#pragma once

#include "Component.h"
#include <map>
#include "dependencies\SDL\include\SDL.h"


class InputComponent : public Component {
public:
	InputComponent(GameObject *);

	//Probably a good idea to unbind the key within the destructor
	~InputComponent();

	virtual void whenPressed() = 0;
};

class InputController{
public:
	static InputController * instance;

	static InputController * getInstance()
	{
		if (!instance)
			instance = new InputController();

		return instance;
	}

	void bindKey(SDL_Keycode, InputComponent *);
	void unbindKey(SDL_Keycode);
	void unbindAction(InputComponent *);
	void swapKeybinds(SDL_Keycode, SDL_Keycode);

	void hitKey(SDL_Keycode);

	~InputController();
private:
	InputController(){};
	std::map<SDL_Keycode, InputComponent*> inputMap;
};