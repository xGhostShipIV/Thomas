#pragma once
#include "Component.h"
#include "../Math/four_dimensions.hpp"

class Rigidbody :
	public Component
{
public:
	Rigidbody(GameObject*);
	~Rigidbody();

	float mass;
	Vec3 centreOfMass;
	bool isKinematic;
	Matrix3 inertiaTensor;
	float CollisionRadius;

	float drag;
	float angularDrag;
	float sleepThreshold;
	float angularSleep;
	Vec3 AngularVelocity;
	Vec3 velocity;
	Vec3 AngularAccel;
	Vec3 accel;

	//Functions
	void AddForce(Vec3);
	void AddTorque(Vec3); //torque in local space
	bool isColliding(GameObject*);
};

