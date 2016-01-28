#include "Rigidbody.h"
#include "GameObject.h"
#include "PhysicsWorld.h"
#include "Component.h"

void Rigidbody::Init(){
	mass = 1;
	centreOfMass = Vec3::Zero();
	isKinematic = true;
	velocity = Vec3::Zero();
	accel = Vec3::Zero();
	CollisionRadius = 0.5f;
	gravitas = true;

	//Always a sphere for now
	float tensorValue = 2.0f / 5.0f * mass * CollisionRadius * CollisionRadius;
	inertiaTensor = Matrix3(
		tensorValue, 0, 0,
		0, tensorValue, 0,
		0, 0, tensorValue);

	//More on this later, for now is percectly ok.
	drag = 0.5f;
	angularDrag = 0.02f;
	sleepThreshold = 0.003f;

	//AngularVelocity = Quat(0, Vec3::Zero());
	//AngularAccel = Quat(0, Vec3::Zero());

	PhysicsWorld::getInstance()->PhysicalObjects.push_back(this);
}

Rigidbody::Rigidbody(GameObject* _parent) : Component(_parent,Component::ComponentType::Rigidbody) {
	if (_parent->getComponent<Collider>() == nullptr){
		col = new SphereCollider(_parent);
	}
	else {
		col = _parent->getComponent<Collider>();
	}
	Init();
}

Rigidbody::Rigidbody(GameObject* _parent, Collider* _Collider) : Component(_parent, Component::ComponentType::Rigidbody){
	col = _Collider;
	Init();
}


Rigidbody::~Rigidbody(){}

void Rigidbody::AddForce(Vec3 _force){
	accel += _force / mass;
}

void Rigidbody::AddTorque(Quat _torque){
	AngularAccel = AngularAccel * _torque;
}