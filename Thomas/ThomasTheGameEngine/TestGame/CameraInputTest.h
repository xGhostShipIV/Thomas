#pragma once
#include <InputComponent.h>
#include <Camera.h>

/*
	A number of input controls to control the camera within the game
*/

#define CameraSpeed 2.5f

class CameraUp : public InputComponent {
	
	Camera* owner;
	
public:
	CameraUp(Camera* _owner, SDL_Keycode key) : owner(_owner), InputComponent(_owner, key) {};

	void whenPressed(float _timestep){
		owner->Translate(Quat::rotate(owner->rotation, Vec3(0, CameraSpeed, 0) * _timestep));
	}
};

class CameraDown : public InputComponent {
	
	Camera* owner;
	
public:
	CameraDown(Camera* _owner, SDL_Keycode key) : owner(_owner), InputComponent(_owner, key) {};

	void whenPressed(float _timestep){
		owner->Translate(Quat::rotate(owner->rotation, Vec3(0, -CameraSpeed, 0) * _timestep));
	}
};

class CameraRight : public InputComponent {
	
	Camera* owner;
	
public:
	CameraRight(Camera* _owner, SDL_Keycode key) : owner(_owner), InputComponent(_owner, key){};
	void whenPressed(float _timestep){
		owner->Translate(Quat::rotate(owner->rotation, Vec3(-CameraSpeed, 0, 0) * _timestep));
	}
};

class CameraLeft : public InputComponent {
	
	Camera* owner;
	
public:
	CameraLeft(Camera* _owner, SDL_Keycode key) : owner(_owner), InputComponent(_owner, key) {};
	void whenPressed(float _timestep){
		owner->Translate(Quat::rotate(owner->rotation, Vec3(CameraSpeed, 0, 0) * _timestep));
	}
};

class CameraForward : public InputComponent {

	Camera* owner;

public:
	CameraForward(Camera* _owner, SDL_Keycode key) : owner(_owner), InputComponent(_owner, key) {};
	void whenPressed(float _timestep){
		owner->Translate(Quat::rotate(owner->rotation, Vec3(0, 0, CameraSpeed) * _timestep));
	}
};

class CameraBackward : public InputComponent {

	Camera* owner;

public:
	CameraBackward(Camera* _owner, SDL_Keycode key) : owner(_owner), InputComponent(_owner, key) {};
	void whenPressed(float _timestep){
		owner->Translate(Quat::rotate(owner->rotation, Vec3(0, 0, -CameraSpeed) * _timestep));
	}
};

class CameraTurnLeft : public InputComponent {

	Camera* owner;

public:
	CameraTurnLeft(Camera* _owner, SDL_Keycode key) : owner(_owner), InputComponent(_owner, key) {};
	void whenPressed(float _timestep){
		owner->Rotate(Quat(CameraSpeed * _timestep, owner->up()));
	}
};

class CameraTurnRight : public InputComponent {

	Camera* owner;

public:
	CameraTurnRight(Camera* _owner, SDL_Keycode key) : owner(_owner), InputComponent(_owner, key) {};
	void whenPressed(float _timestep){
		owner->Rotate(Quat(-CameraSpeed * _timestep, owner->up()));
	}
};

class CameraTurnDown : public InputComponent {

	Camera* owner;

public:
	CameraTurnDown(Camera* _owner, SDL_Keycode key) : owner(_owner), InputComponent(_owner, key) {};
	void whenPressed(float _timestep){
		owner->Rotate(Quat(-CameraSpeed * _timestep, Vec3::cross(owner->forward(), owner->up())));
	}
};

class CameraTurnUp : public InputComponent {

	Camera* owner;

public:
	CameraTurnUp(Camera* _owner, SDL_Keycode key) : owner(_owner), InputComponent(_owner, key) {};
	void whenPressed(float _timestep){
		owner->Rotate(Quat(CameraSpeed * _timestep, Vec3::cross(owner->forward(),owner->up())));
	}
};

class CameraRollLeft : public InputComponent {

	Camera* owner;

public:
	CameraRollLeft(Camera* _owner, SDL_Keycode key) : owner(_owner), InputComponent(_owner, key) {};
	void whenPressed(float _timestep){
		owner->Rotate(Quat(-CameraSpeed * _timestep, owner->forward()));
	}
};

class CameraRollRight : public InputComponent {

	Camera* owner;

public:
	CameraRollRight(Camera* _owner, SDL_Keycode key) : owner(_owner), InputComponent(_owner, key) {};
	void whenPressed(float _timestep){
		owner->Rotate(Quat(CameraSpeed * _timestep, owner->forward()));
	}
};

class CameraResetOrientation : public InputComponent {

	Camera* owner;

public:
	CameraResetOrientation(Camera* _owner, SDL_Keycode key) : owner(_owner), InputComponent(_owner, key) {};
	void whenPressed(float _timestep){
		//owner->Rotate(owner->rotation.inverse().vector);
		owner->LookAt(Vec3(0, 0, 0));
	}
};

