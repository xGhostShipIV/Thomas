#pragma once
#include <InputComponent.h>
#include <Camera.h>

/*
A number of input controls to control the camera within the game like an fps
*/

#define FPSMoveSpeed 5.0f
#define FPSHorizontalTurnSpeed 7.5f
#define FPSVerticalTurnSpeed 7.5f

class FPS_STRAFE_RIGHT : public InputComponent {

	Camera* owner;

public:
	FPS_STRAFE_RIGHT(Camera* _owner, SDL_Keycode key) : owner(_owner), InputComponent(_owner, key){};
	void whenPressed(float _timestep){
		owner->Translate(Quat::rotate(Quat(owner->rotation.w, 0, owner->rotation.vector.y, 0).NormalizeThis(), Vec3(-FPSMoveSpeed, 0, 0) * _timestep));
	}
};

class FPS_STRAFE_LEFT : public InputComponent {

	Camera* owner;

public:
	FPS_STRAFE_LEFT(Camera* _owner, SDL_Keycode key) : owner(_owner), InputComponent(_owner, key) {};
	void whenPressed(float _timestep){
		owner->Translate(Quat::rotate(Quat(owner->rotation.w, 0, owner->rotation.vector.y, 0).NormalizeThis(), Vec3(FPSMoveSpeed, 0, 0) * _timestep));
	}
};

class FPS_FORWARD : public InputComponent {

	Camera* owner;

public:
	FPS_FORWARD(Camera* _owner, SDL_Keycode key) : owner(_owner), InputComponent(_owner, key) {};
	void whenPressed(float _timestep){
		owner->Translate(Quat::rotate(Quat(owner->rotation.w, 0, owner->rotation.vector.y, 0).NormalizeThis(), Vec3(0, 0, FPSMoveSpeed) * _timestep));
	}
};

class FPS_BACKWARD : public InputComponent {

	Camera* owner;

public:
	FPS_BACKWARD(Camera* _owner, SDL_Keycode key) : owner(_owner), InputComponent(_owner, key) {};
	void whenPressed(float _timestep){
		owner->Translate(Quat::rotate(Quat(owner->rotation.w, 0, owner->rotation.vector.y, 0).NormalizeThis(), Vec3(0, 0, -FPSMoveSpeed) * _timestep));
	}
};

class FPS_TURN_LEFT : public InputComponent {

	Camera* owner;

public:
	FPS_TURN_LEFT(Camera* _owner, MouseMovement _event) : owner(_owner), InputComponent(_owner, _event) {};
	void whenPressed(float _timestep){
		owner->Rotate(Quat(FPSHorizontalTurnSpeed * _timestep, Vec3::BasisY()));
	}
};

class FPS_TURN_RIGHT : public InputComponent {

	Camera* owner;

public:
	FPS_TURN_RIGHT(Camera* _owner, MouseMovement _event) : owner(_owner), InputComponent(_owner, _event) {};
	void whenPressed(float _timestep){
		owner->Rotate(Quat(-FPSHorizontalTurnSpeed * _timestep, Vec3::BasisY()));
	}
};

class FPS_TURN_UP : public InputComponent {

	Camera* owner;

public:
	FPS_TURN_UP(Camera* _owner, MouseMovement _event) : owner(_owner), InputComponent(_owner, _event) {};
	void whenPressed(float _timestep){
		owner->Rotate(Quat(-FPSVerticalTurnSpeed * _timestep * Vec3::cross(owner->forward(), owner->up()).length(), Vec3::cross(owner->forward(), owner->up())));

		/*float yRotation = owner->rotation.vector.y / (sin(acos(owner->rotation.w) * 2) / 2.0f);

		if (yRotation > 180 * 3.141592654f / 180.0f)
		{
			owner->Rotate(Quat(yRotation - 180 * 3.141592654f / 180.0f, Vec3::cross(owner->forward(), owner->up())));
		}*/
	}
};


class FPS_TURN_DOWN : public InputComponent {

	Camera* owner;

public:
	FPS_TURN_DOWN(Camera* _owner, MouseMovement _event) : owner(_owner), InputComponent(_owner, _event) {};
	void whenPressed(float _timestep){
		owner->Rotate(Quat(FPSVerticalTurnSpeed * _timestep * Vec3::cross(owner->forward(), owner->up()).length(), Vec3::cross(owner->forward(), owner->up())));


		/*float yRotation = owner->rotation.vector.y / (sin(acos(owner->rotation.w) * 2) / 2.0f);

		if (yRotation < 0 * 3.141592654f / 180.0f)
		{
			owner->Rotate(Quat(0 - yRotation, Vec3::cross(owner->forward(), owner->up())));
		}*/
	}
};
