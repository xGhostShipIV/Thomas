#pragma once

#include "Component.h"
#include <map>
#include <vector>
#include "dependencies\SDL\include\SDL.h"

/*
	A component to define an action desired to be taken when a 
	particular key has been pressed. Because it is abstract,
	derived classes must be made to specify behaviour.
*/
class InputComponent : public Component {
public:
	InputComponent(GameObject *);
	~InputComponent();

	//Abstract method that defines the action to be taken when the associated
	//Key has been pressed.
	virtual void whenPressed() = 0;
};


//A static class that acts as a message hub for all input
class InputController{
public:

	//singleton instance
	static InputController * instance;

	static InputController * getInstance()
	{
		if (!instance)
			instance = new InputController();

		return instance;
	}

	//Binds the given keycode with the given InputComponent
	void bindKey(SDL_Keycode, InputComponent *);

	//Deletes the actions associated with the given keybind
	void unbindKey(SDL_Keycode);

	//Deletes the provided action
	void unbindAction(InputComponent *);

	//Trades the actions at the given keys
	void swapKeybinds(SDL_Keycode, SDL_Keycode);

	//Called from the main loop when a key is hit, this will access the inputMap
	//and call the appropriate action
	void hitKey(SDL_Keycode);

	void releaseKey(SDL_Keycode);

	void Update();

	~InputController();
private:
	InputController(){};

	//A map to link keycodes to actions
	std::map<SDL_Keycode, InputComponent*> inputMap;

	std::vector<SDL_Keycode> keysDown;
};