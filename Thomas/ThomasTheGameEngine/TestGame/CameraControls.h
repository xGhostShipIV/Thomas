#pragma once
#include <InputComponent.h>
#include <GameObject.h>

class GameCamera;
class GameLevel;

class CameraControls
{
public:
	CameraControls();
	~CameraControls();
};

class Camera_Forward : public InputComponent
{
public:
	GameCamera * owner;

	Camera_Forward(GameObject* _owner, SDL_Keycode key_);
	
	void whenPressed(float _timestep);
	void whenReleased(){}
};

class Camera_Right : public InputComponent
{
public:
	GameCamera * owner;

	Camera_Right(GameObject* _owner, SDL_Keycode key);

	void whenPressed(float _timestep);
	void whenReleased(){}
};

class Camera_Left : public InputComponent
{
public:
	GameCamera * owner;

	Camera_Left(GameObject* _owner, SDL_Keycode key);

	void whenPressed(float _timestep);
	void whenReleased(){}
};

class Camera_Back : public InputComponent
{
public:
	GameCamera * owner;

	Camera_Back(GameObject* _owner, SDL_Keycode key);

	void whenPressed(float _timestep);
	void whenReleased(){}
};

class LeftClick : public InputComponent
{
	GameCamera * owner;
	bool isSet;

public:
	LeftClick(GameObject * owner_, SDL_Keycode key_);

	void whenPressed(float timeStep_);
	void whenReleased();
};

class RightClick : public InputComponent
{
	GameLevel * gl;

public:
	RightClick(GameObject * owner_, SDL_Keycode key_);

	void whenPressed(float timeStep_);
	void whenReleased();
};

class Look_Up : public InputComponent
{
	GameCamera * owner;

public:
	Look_Up(GameObject * owner_, MouseMovement e_);
	void whenPressed(float timeStep_);
	void whenReleased(){}
};

class Look_Down : public InputComponent
{
	GameCamera * owner;

public:
	Look_Down(GameObject * owner_, MouseMovement e_);
	void whenPressed(float timeStep_);
	void whenReleased(){}
};

class Look_Right : public InputComponent
{
	GameCamera * owner;
	GameLevel * gl;

public:
	Look_Right(GameObject * owner_, MouseMovement e_);
	void whenPressed(float timeStep_);
	void whenReleased(){}
};

class Look_Left : public InputComponent
{
	GameCamera * owner;
	GameLevel * gl;

public:
	Look_Left(GameObject * owner_, MouseMovement e_);
	void whenPressed(float timeStep_);
	void whenReleased(){}
};

