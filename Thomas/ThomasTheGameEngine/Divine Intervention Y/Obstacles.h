#pragma once

#include <GameObject.h>
#include "DIY_Level.h"
#include <PhysicsWorld.h>

class Satellite : public GameObject{
private:
	float orbitSpeed;
	Vec3 orbitAxis;
	Planet* planet;
public:
	//Satellite();
	Satellite(DIY_Level* level_,Planet* planet_, Vec3 starticPos_, Vec3 inPlaneVector_, float orbitSpeed_);
	~Satellite();

	void Update(float _deltaTime) override;
};