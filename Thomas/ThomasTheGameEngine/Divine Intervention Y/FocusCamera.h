#pragma once

#include <Camera.h>

class FocusCamera : public Camera{
	GameObject * focus;
	float followDistance;
	float MaxCameraDistance, MinCameraDistance;
	enum LookState{
		Stare,
		Peek,
		Orbit
	};

	LookState behaviour;

	Vec3 selfieStick;
public:
	FocusCamera(Level * level_, GameObject * focus_, Vec3 position_);
	~FocusCamera();

	void Update(float deltatime_) override;

	void ChangeFocus(GameObject* newFocus_);
	void ChangeDistance(float newFollow_);
	void SetMaxDistance(float maxDistance_);
	void SetMinDistance(float minDistance_);
};