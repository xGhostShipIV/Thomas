#pragma once

#include <Camera.h>
#include <States.h>
#include "DIY_Level.h"

class FocusCamera : public Camera{
	GameObject * focus;
	float followDistance;
	float MaxCameraDistance, MinCameraDistance;
	enum LookState{
		Stare,
		Peek,
		Orbit,
		Pan
	};

	Vec3 selfieStick;

	//these two should be either 1 or -1 for mouse movement inversion
	int xInverted, yInverted;

	//more camera control numbers.
	float lookSpeed;
	

	LookState behaviour;
	friend class Stare;
	friend class Peek;
	friend class Orbit;
	friend class Refocus;

public:
	FocusCamera(Level * level_, GameObject * focus_, Vec3 position_);
	~FocusCamera();

	StateMachine stateMachine;

	void Update(float deltatime_) override;

	GameObject * getFocus();
	void ChangeFocus(GameObject* newFocus_);
	void ChangeDistance(float newFollow_);
	void SetMaxDistance(float maxDistance_);
	void SetMinDistance(float minDistance_);
	void startPan(float duration_, Wormhole* guider);
};

//States for the state machine.-------------------------------------------
class Stare : public State {
public:
	Stare(void*);
	~Stare();
	void Execute() override;
	void onEnter() override;
	void onExit() override;
};

class Peek : public State {
private:
	Quat beginningOrientation;
public:
	Peek(void*);
	~Peek();
	void Execute() override;
	void onEnter() override;
	void onExit() override;
};

class Orbit : public State {
public:
	Orbit(void*);
	~Orbit();
	void Execute() override;
	void onEnter() override;
	void onExit() override;
};

class Refocus : public State {
	float maxTime;

	//With respect to time:
	float dR, dTheta;

	//Current values
	float curR, curTime;
	Vec3 sunSelfieStick; //Makes positioning easy

	//Needed data for facilitation
	Wormhole* guidance;
	bool isNextLayerSet;

	Quat cameraOrientation;

public:
	Refocus(float duration, Wormhole* destination_, void* self);
	~Refocus();
	void Execute() override;
	void onEnter() override;
	void onExit() override;
};