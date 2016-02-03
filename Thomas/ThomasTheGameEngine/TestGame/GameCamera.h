//Author: Nathan Senter
//Date: 28/01/2016

#pragma once

#include <Camera.h>
#include "CameraControls.h"

class GameCamera : public Camera
{

public:
	bool mouseDown;

	//Will store the forward vector when you begin rotating. Will be the reference to return to its
	//original look at position when the mouse is released
	Vec3 originalLookat;
	Quat originalRotation;

	GameCamera(Level * level_, Vec3 position_, Vec3 lookAt_);
	~GameCamera();

	void Update(float _deltaTime) override;

	Camera_Forward * cf;
	Camera_Back * cb;
	Camera_Left * cl;
	Camera_Right * cr;

	LeftClick * lc;

	Look_Up * lu;
	Look_Down * ld;
	Look_Right * lr;
	Look_Left * ll;
};