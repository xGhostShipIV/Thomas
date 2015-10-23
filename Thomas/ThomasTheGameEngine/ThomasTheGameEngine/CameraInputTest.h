#pragma once
#include "InputComponent.h"
#include "Camera.h"

class CameraUp : public InputComponent {
	
	Camera* owner;
	
public:
	CameraUp(Camera* _owner) : owner(_owner) {};

	void whenPressed(){
		owner->CameraPosition.y += 0.1f;
	}
};

class CameraDown : public InputComponent {
	
	Camera* owner;
	
public:
	CameraDown(Camera* _owner) : owner(_owner) {};

	void whenPressed(){
		owner->CameraPosition.y -= 0.1f;
	}
};

class CameraRight : public InputComponent {
	
	Camera* owner;
	
public:
	CameraRight(Camera* _owner) : owner(_owner) {};
	void whenPressed(){
		owner->CameraPosition.x += 0.1f;
	}
};

class CameraLeft : public InputComponent {
	
	Camera* owner;
	
public:
	CameraLeft(Camera* _owner) : owner(_owner) {};
	void whenPressed(){
		owner->CameraPosition.x -= 0.1f;
	}
};

class CameraForward : public InputComponent {

	Camera* owner;

public:
	CameraForward(Camera* _owner) : owner(_owner) {};
	void whenPressed(){
		owner->CameraPosition.z += 0.1f;
	}
};

class CameraBackward : public InputComponent {

	Camera* owner;

public:
	CameraBackward(Camera* _owner) : owner(_owner) {};
	void whenPressed(){
		owner->CameraPosition.z -= 0.1f;
	}
};