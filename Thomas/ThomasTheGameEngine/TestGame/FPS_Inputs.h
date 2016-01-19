#pragma once
#include <InputComponent.h>
#include <Camera.h>
#include <cmath>
#include <Rigidbody.h>
/*
A number of input controls to control the camera within the game like an fps
*/

static float FPSMoveSpeed = 1.0f;
static float FPSHorizontalTurnSpeed = 2.5f;
static float FPSVerticalTurnSpeed = 1.5f;

class FPS_SPEED
{
public:
	static void SetSpeed(float _moveSpeed, float _hTurnSpeed, float _vTurnSpeed)
	{
		FPSMoveSpeed = _moveSpeed;
		FPSHorizontalTurnSpeed = _hTurnSpeed;
		FPSVerticalTurnSpeed = _vTurnSpeed;
	}
};

class FPS_STRAFE_RIGHT : public InputComponent {

	GameObject* owner;

public:
	FPS_STRAFE_RIGHT(GameObject* _owner, SDL_Keycode key) : owner(_owner), InputComponent(_owner, key){};
	void whenPressed(float _timestep){
		owner->Translate(Quat::rotate(Quat(owner->rotation.w, 0, owner->rotation.vector.y, 0).NormalizeThis(), Vec3(-FPSMoveSpeed, 0, 0) * _timestep));
	}
};

class FPS_STRAFE_LEFT : public InputComponent {

	GameObject* owner;

public:
	FPS_STRAFE_LEFT(GameObject* _owner, SDL_Keycode key) : owner(_owner), InputComponent(_owner, key) {};
	void whenPressed(float _timestep){
		owner->Translate(Quat::rotate(Quat(owner->rotation.w, 0, owner->rotation.vector.y, 0).NormalizeThis(), Vec3(FPSMoveSpeed, 0, 0) * _timestep));

	}
};

class FPS_FORWARD : public InputComponent {

	GameObject* owner;

public:
	FPS_FORWARD(GameObject* _owner, SDL_Keycode key) : owner(_owner), InputComponent(_owner, key) {};
	void whenPressed(float _timestep){
		owner->Translate(Quat::rotate(Quat(owner->rotation.w, 0, owner->rotation.vector.y, 0).NormalizeThis(), Vec3(0, 0, FPSMoveSpeed) * _timestep));
	}
};

class FPS_BACKWARD : public InputComponent {

	GameObject* owner;

public:
	FPS_BACKWARD(GameObject* _owner, SDL_Keycode key) : owner(_owner), InputComponent(_owner, key) {};
	void whenPressed(float _timestep){
		owner->Translate(Quat::rotate(Quat(owner->rotation.w, 0, owner->rotation.vector.y, 0).NormalizeThis(), Vec3(0, 0, -FPSMoveSpeed) * _timestep));
	}
};

class FPS_TURN_LEFT : public InputComponent {

	GameObject* owner;

public:
	FPS_TURN_LEFT(GameObject* _owner, MouseMovement _event) : owner(_owner), InputComponent(_owner, _event) {};
	void whenPressed(float _timestep){
		owner->Rotate(Quat(FPSHorizontalTurnSpeed * _timestep, Vec3::BasisY()));
	}
};

class FPS_TURN_RIGHT : public InputComponent {

	GameObject* owner;

public:
	FPS_TURN_RIGHT(GameObject* _owner, MouseMovement _event) : owner(_owner), InputComponent(_owner, _event) {};
	void whenPressed(float _timestep){
		owner->Rotate(Quat(-FPSHorizontalTurnSpeed * _timestep, Vec3::BasisY()));
	}
};

class FPS_TURN_UP : public InputComponent {

	GameObject* owner;

public:
	FPS_TURN_UP(GameObject* _owner, MouseMovement _event) : owner(_owner), InputComponent(_owner, _event) {};
	void whenPressed(float _timestep){
		owner->Rotate(Quat(-FPSVerticalTurnSpeed * _timestep * Vec3::cross(owner->forward(), owner->up()).length(), Vec3::cross(owner->forward(), owner->up())));
	}
};


class FPS_TURN_DOWN : public InputComponent {

	GameObject* owner;

public:
	FPS_TURN_DOWN(GameObject* _owner, MouseMovement _event) : owner(_owner), InputComponent(_owner, _event) {};
	void whenPressed(float _timestep){
		owner->Rotate(Quat(FPSVerticalTurnSpeed * _timestep * Vec3::cross(owner->forward(), owner->up()).length(), Vec3::cross(owner->forward(), owner->up())));
	}
};

class FPS_MOVE_UP : public InputComponent
{

	GameObject* owner;

public:
	FPS_MOVE_UP(GameObject* _owner, SDL_Keycode key) : owner(_owner), InputComponent(_owner, key) {};

	void whenPressed(float _timestep){
		owner->Translate(Vec3(0, FPSMoveSpeed, 0) * _timestep);
	}
};

class FPS_MOVE_DOWN : public InputComponent
{
	GameObject* owner;

public:
	FPS_MOVE_DOWN(GameObject* _owner, SDL_Keycode key) : owner(_owner), InputComponent(_owner, key) {};

	void whenPressed(float _timestep){
		owner->Translate(Vec3(0, -FPSMoveSpeed, 0) * _timestep);
	}
};