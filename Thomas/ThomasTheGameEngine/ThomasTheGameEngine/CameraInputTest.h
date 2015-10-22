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
	void whenPressed(){
		owner->CameraPosition.y -= 0.1f;
	}
};

class CameraRight : public InputComponent {
	
	Camera* owner;
	
public:
	void whenPressed(){
		owner->CameraPosition.x += 0.1f;
	}
};

class CameraLeft : public InputComponent {
	
	Camera* owner;
	
public:
	void whenPressed(){
		owner->CameraPosition.x -= 0.1f;
	}
};