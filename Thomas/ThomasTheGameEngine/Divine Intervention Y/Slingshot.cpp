#include "Slingshot.h"
#include <GameObject.h>
#include <PhysicsWorld.h>

Slingshot::Slingshot(Rigidbody* cue_, GameObject* planetoid_){
	cueball = cue_;
	planetoid = planetoid_;
	totalAngle = 0.0f;
	stepAngle = Vec3::length(cueball->velocity) / Vec3::length(cueball->parentObject->position - planetoid->position);

	orbitQuat = Quat(Vec3::length(cueball->velocity) / Vec3::length(cueball->parentObject->position - planetoid->position),
		Vec3::cross(cueball->velocity.Normalized(), (cueball->parentObject->position - planetoid->position).Normalized()));

	isCaught = true;
}

void Slingshot::Update(float deltaTime_){

	if (isCaught){
		Quat::rotate(orbitQuat, cueball->velocity);
		cueball->parentObject->Translate(Quat::rotate(orbitQuat, cueball->parentObject->position - planetoid->position) - (cueball->parentObject->position - planetoid->position));

		totalAngle += stepAngle;
	}

	if (stepAngle >= M_PI){
		isCaught = false;
		cueball->isKinematic = true;
	}
}