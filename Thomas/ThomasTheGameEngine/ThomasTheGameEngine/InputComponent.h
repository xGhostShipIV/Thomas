#pragma once

#include "Component.h"
#include <map>
#include <vector>
#include "dependencies\SDL\include\SDL.h"
#include "../Math/four_dimensions.hpp"
#include <SDL.h>

//For binding multiple keys
#define BindKey Game::GetInstance()->inputManager->bindKey

enum MouseMovement
{
	None, Positive_X, Negative_X, Positive_Y, Negative_Y
};

/*
	A component to define an action desired to be taken when a 
	particular key has been pressed. Because it is abstract,
	derived classes must be made to specify behaviour.
*/
class InputComponent : public Component {
public:
	InputComponent(GameObject *, SDL_Keycode key);
	InputComponent(GameObject *, MouseMovement _event);
	~InputComponent();

	//Abstract method that defines the action to be taken when the associated
	//Key has been pressed.
	virtual void whenPressed(float _timestep) = 0;
	virtual void whenReleased() = 0;

	bool hasBeenPressed;
};


//A static class that acts as a message hub for all input
class InputController{
public:
	/* TESTING PURPOSES */
	SDL_MouseMotionEvent MoEvent;

	//singleton instance
	static InputController * instance;

	static InputController * getInstance()
	{
		if (!instance)
			instance = new InputController();

		return instance;
	}

	void handleEvents(SDL_Event event_, float _timestep);

	int MouseX, MouseY;
	int PreviousMouseX, PreviousMouseY;
	Uint32 MouseState, PreviousMouseState;

	std::map<Uint8, SDL_Keycode> mouseButtonDict;

	//Binds the given keycode with the given InputComponent, 
	//returns InputComponent back for multiple keybinds
	InputComponent* bindKey(SDL_Keycode, InputComponent *);

	InputComponent* bindMouseEvent(MouseMovement, InputComponent *);

	//Deletes the actions associated with the given keybind
	void unbindKey(SDL_Keycode);

	void unbindMouseEvent(MouseMovement);

	//Deletes the provided action
	void unbindAction(InputComponent *);

	//Trades the actions at the given keys
	void swapKeybinds(SDL_Keycode, SDL_Keycode);

	//Called from the main loop when a key is hit, this will access the inputMap
	//and call the appropriate action
	void hitKey(SDL_Keycode);

	void releaseKey(SDL_Keycode);

	void mouseMovement(SDL_MouseMotionEvent _event, float _timestep);

	void Update(float _timestep);

	~InputController();
private:
	//A map to link keycodes to actions
	std::map<SDL_Keycode, InputComponent*> inputMap;
	std::map<MouseMovement, InputComponent*> motionMap;

	std::vector<SDL_Keycode> keysDown;

	InputController();
};