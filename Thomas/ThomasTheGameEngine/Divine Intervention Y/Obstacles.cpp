#include "Obstacles.h"

Satellite::Satellite(DIY_Level* level_,Planet* planet_, Vec3 startingPos_, Vec3 inPlaneVector_, float orbitSpeed_) : GameObject(level_, startingPos_), orbitSpeed(orbitSpeed_), planet(planet_){
	orbitAxis = Vec3::cross(startingPos_ - planet_->position, inPlaneVector_);
	new Rigidbody(this, new SphereCollider(this));
}

void Satellite::Update(float deltaTime_){
	RotateAround(planet->position, orbitAxis, orbitSpeed);
}