#include "Rigidbody.h"
#include "GameObject.h"
#include "PhysicsWorld.h"

Rigidbody::Rigidbody(GameObject* _parent) : Component(_parent,Component::ComponentType::Rigidbody)
{
	mass = 1;
	centreOfMass = Vec3::Zero();
	isKinematic = true;
	velocity = Vec3::Zero();
	accel = Vec3::Zero();
	CollisionRadius = 1;
	//AngularVelocity = Quat(0, Vec3::Zero());
	//AngularAccel = Quat(0, Vec3::Zero());

	//Build the intertia tensor, they are always spheres right now:
	float tensorValue = 2.f / 5.f * mass * CollisionRadius * CollisionRadius;
	inertiaTensor = Matrix3(
		tensorValue, 0, 0,
		0, tensorValue, 0,
		0, 0, tensorValue);

	//To be fixed when we get the rest of our math implemented.
	drag = 0.002f;
	angularDrag = 0.002f;
	sleepThreshold = 0.00001f;

	PhysicsWorld::getInstance()->PhysicalObjects.push_back(this);
}


Rigidbody::~Rigidbody()
{
}

void Rigidbody::AddForce(Vec3 _force){
	accel += _force / mass;
}

void Rigidbody::AddTorque(Vec3 _torque){
	AngularAccel += _torque;
}

bool Rigidbody::isColliding(GameObject* other){
	if (Vec3::length(parentObject->position - other->position) < (CollisionRadius + other->getComponent<Rigidbody>()->CollisionRadius)){
		return true;
	}else{
		return false;
	}
}