#pragma once
#include <InputComponent.h>
#include <Camera.h>

class CameraUp : public InputComponent {
	
	Camera* owner;
	
public:
	CameraUp(Camera* _owner) : owner(_owner), InputComponent(_owner) {};

	void whenPressed(){
		owner->transform->position.y += 0.1f;
	}
};

class CameraDown : public InputComponent {
	
	Camera* owner;
	
public:
	CameraDown(Camera* _owner) : owner(_owner), InputComponent(_owner) {};

	void whenPressed(){
		owner->transform->position.y -= 0.1f;
	}
};

class CameraRight : public InputComponent {
	
	Camera* owner;
	
public:
	CameraRight(Camera* _owner) : owner(_owner), InputComponent(_owner){};
	void whenPressed(){
		owner->transform->position.x -= 0.1f;
	}
};

class CameraLeft : public InputComponent {
	
	Camera* owner;
	
public:
	CameraLeft(Camera* _owner) : owner(_owner), InputComponent(_owner) {};
	void whenPressed(){
		owner->transform->position.x += 0.1f;
	}
};

class CameraForward : public InputComponent {

	Camera* owner;

public:
	CameraForward(Camera* _owner) : owner(_owner), InputComponent(_owner) {};
	void whenPressed(){
		owner->transform->position.z += 0.1f;
	}
};

class CameraBackward : public InputComponent {

	Camera* owner;

public:
	CameraBackward(Camera* _owner) : owner(_owner), InputComponent(_owner) {};
	void whenPressed(){
		owner->transform->position.z -= 0.1f;
	}
};

class CameraTurnLeft : public InputComponent {

	Camera* owner;

public:
	CameraTurnLeft(Camera* _owner) : owner(_owner), InputComponent(_owner) {};
	void whenPressed(){
		owner->transform->Rotate(Vec3(0, 0.1f, 0));
	}
};

class CameraTurnRight : public InputComponent {

	Camera* owner;

public:
	CameraTurnRight(Camera* _owner) : owner(_owner), InputComponent(_owner) {};
	void whenPressed(){
		owner->transform->Rotate(Vec3(0, -0.1f, 0));
	}
};

class CameraTurnDown : public InputComponent {

	Camera* owner;

public:
	CameraTurnDown(Camera* _owner) : owner(_owner), InputComponent(_owner) {};
	void whenPressed(){
		owner->transform->Rotate(Vec3(0.1f, 0, 0));
	}
};

class CameraTurnUp : public InputComponent {

	Camera* owner;

public:
	CameraTurnUp(Camera* _owner) : owner(_owner), InputComponent(_owner) {};
	void whenPressed(){
		owner->transform->Rotate(Vec3(-0.1f, 0, 0));
	}
};