#pragma once
#include <InputComponent.h>
#include <Camera.h>

/*
	A number of input controls to control the camera within the game
*/

#define CameraSpeed 2.5f

class CameraUp : public InputComponent {
	
	GameObject* owner;
	
public:
	CameraUp(GameObject* _owner, SDL_Keycode key) : owner(_owner), InputComponent(_owner, key) {};

	void whenPressed(float _timestep){
		owner->Translate(Quat::rotate(owner->rotation, Vec3(0, CameraSpeed, 0) * _timestep));
	}
};

class CameraDown : public InputComponent {
	
	GameObject* owner;
	
public:
	CameraDown(GameObject* _owner, SDL_Keycode key) : owner(_owner), InputComponent(_owner, key) {};

	void whenPressed(float _timestep){
		owner->Translate(Quat::rotate(owner->rotation, Vec3(0, -CameraSpeed, 0) * _timestep));
	}
};

class CameraRight : public InputComponent {
	
	GameObject* owner;
	
public:
	CameraRight(GameObject* _owner, SDL_Keycode key) : owner(_owner), InputComponent(_owner, key){};
	void whenPressed(float _timestep){
		owner->Translate(Quat::rotate(owner->rotation, Vec3(-CameraSpeed, 0, 0) * _timestep));
	}
};

class CameraLeft : public InputComponent {
	
	GameObject* owner;
	
public:
	CameraLeft(GameObject* _owner, SDL_Keycode key) : owner(_owner), InputComponent(_owner, key) {};
	void whenPressed(float _timestep){
		owner->Translate(Quat::rotate(owner->rotation, Vec3(CameraSpeed, 0, 0) * _timestep));
	}
};

class CameraForward : public InputComponent {

	GameObject* owner;

public:
	CameraForward(GameObject* _owner, SDL_Keycode key) : owner(_owner), InputComponent(_owner, key) {};
	void whenPressed(float _timestep){
		owner->Translate(Quat::rotate(owner->rotation, Vec3(0, 0, CameraSpeed) * _timestep));
	}
};

class CameraBackward : public InputComponent {

	GameObject* owner;

public:
	CameraBackward(GameObject* _owner, SDL_Keycode key) : owner(_owner), InputComponent(_owner, key) {};
	void whenPressed(float _timestep){
		owner->Translate(Quat::rotate(owner->rotation, Vec3(0, 0, -CameraSpeed) * _timestep));
	}
};

class CameraTurnLeft : public InputComponent {

	GameObject* owner;

public:
	CameraTurnLeft(GameObject* _owner, SDL_Keycode key) : owner(_owner), InputComponent(_owner, key) {};
	void whenPressed(float _timestep){
		owner->Rotate(Quat(CameraSpeed * _timestep, owner->up()));
	}
};

class CameraTurnRight : public InputComponent {

	GameObject* owner;

public:
	CameraTurnRight(GameObject* _owner, SDL_Keycode key) : owner(_owner), InputComponent(_owner, key) {};
	void whenPressed(float _timestep){
		owner->Rotate(Quat(-CameraSpeed * _timestep, owner->up()));
	}
};

class CameraTurnDown : public InputComponent {

	GameObject* owner;

public:
	CameraTurnDown(GameObject* _owner, SDL_Keycode key) : owner(_owner), InputComponent(_owner, key) {};
	void whenPressed(float _timestep){
		owner->Rotate(Quat(-CameraSpeed * _timestep, Vec3::cross(owner->forward(), owner->up())));
	}
};

class CameraTurnUp : public InputComponent {

	GameObject* owner;

public:
	CameraTurnUp(GameObject* _owner, SDL_Keycode key) : owner(_owner), InputComponent(_owner, key) {};
	void whenPressed(float _timestep){
		owner->Rotate(Quat(CameraSpeed * _timestep, Vec3::cross(owner->forward(),owner->up())));
	}
};

class CameraRollLeft : public InputComponent {

	GameObject* owner;

public:
	CameraRollLeft(GameObject* _owner, SDL_Keycode key) : owner(_owner), InputComponent(_owner, key) {};
	void whenPressed(float _timestep){
		owner->Rotate(Quat(-CameraSpeed * _timestep, owner->forward()));
	}
};

class CameraRollRight : public InputComponent {

	GameObject* owner;

public:
	CameraRollRight(GameObject* _owner, SDL_Keycode key) : owner(_owner), InputComponent(_owner, key) {};
	void whenPressed(float _timestep){
		owner->Rotate(Quat(CameraSpeed * _timestep, owner->forward()));
	}
};

class CameraResetOrientation : public InputComponent {

	GameObject* owner;

public:
	CameraResetOrientation(GameObject* _owner, SDL_Keycode key) : owner(_owner), InputComponent(_owner, key) {};
	void whenPressed(float _timestep){
		//owner->Rotate(owner->rotation.inverse().vector);
		owner->LookAt(Vec3(0, 0, 0));
	}
};

