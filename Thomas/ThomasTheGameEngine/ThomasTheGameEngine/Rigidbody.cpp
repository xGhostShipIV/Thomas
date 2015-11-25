#include "Rigidbody.h"

Rigidbody::Rigidbody(GameObject* _parent) : Component(_parent,Component::ComponentType::Rigidbody)
{
	mass = 1;
	centreOfMass = Vec3::Zero();
	isKinematic = true;
	velocity = Vec3::Zero();
	accel = Vec3::Zero();
	CollisionRadius = 1;

	//Build the intertia tensor, they are always spheres right now:
	float tensorValue = 2.f / 5.f * mass * CollisionRadius * CollisionRadius;
	inertiaTensor = Matrix3(
		tensorValue, 0, 0,
		0, tensorValue, 0,
		0, 0, tensorValue);

	//To be fixed when we get the rest of our math implemented.
	drag = 1;
	angularDrag = 1;
	sleepThreshold = 1;
}


Rigidbody::~Rigidbody()
{
}

void Rigidbody::AddForce(Vec3 _force){
	accel += _force / mass;
}

void Rigidbody::AddTorque(Quat _torque){
	AngularAccel = _torque * AngularAccel;
}