#include "PhysicsWorld.h"
#include "Rigidbody.h"


PhysicsWorld::PhysicsWorld()
{
}


PhysicsWorld::~PhysicsWorld()
{
}

float PhysicsWorld::Impulse(GameObject* _first, GameObject*_second){
	float epsilon = 1; //Worry more about this later
	Vec3 normal = (_first->position - _second->position).Normalized();
	Rigidbody* firstBody = _first->getComponent<Rigidbody>();
	Rigidbody* secondBody = _second->getComponent<Rigidbody>();

	//Yes this is messy, don't touch
	float J = Vec3::dot(normal, secondBody->velocity - firstBody->velocity) * (1 + epsilon) /
		(1 / firstBody->mass + 1 / secondBody->mass +
		Vec3::dot(normal, firstBody->inertiaTensor.inverse() * Vec3::cross(Vec3::cross((firstBody->CollisionRadius * normal), normal), normal * firstBody->CollisionRadius)) +
		Vec3::dot(normal, secondBody->inertiaTensor.inverse() * Vec3::cross(Vec3::cross((-secondBody->CollisionRadius * normal), normal), normal * -secondBody->CollisionRadius)));

	return J;
}

void PhysicsWorld::Update(UINT32 _deltaTime){
	
	{
		//Scope already defined, just slap in if statment around this sucka
		GameObject* testOne = new GameObject();
		GameObject* testTwo = new GameObject();

		Rigidbody* testBodyOne = testOne->getComponent<Rigidbody>();
		Rigidbody* testBodyTwo = testTwo->getComponent<Rigidbody>();

		float J = PhysicsWorld::Impulse(testOne, testTwo);

		testBodyOne->accel += (testTwo->position - testOne->position) * J / testBodyOne->mass;
		testBodyTwo->accel += (testOne->position - testTwo->position) * J / testBodyOne->mass;

		testBodyOne->AngularAccel = testBodyOne->AngularAccel * Quat::Identity() * (testBodyOne->inertiaTensor.inverse() * ((testTwo->position - testOne->position) * J *testBodyOne->CollisionRadius));
		testBodyTwo->AngularAccel = testBodyTwo->AngularAccel * Quat::Identity() * (testBodyTwo->inertiaTensor.inverse() * ((testOne->position - testTwo->position) * J *testBodyTwo->CollisionRadius));
	}

	for (auto it = PhysicalObjects.begin(); it != PhysicalObjects.end(); it++){
		it->AddForce(worldGravity);
	}

	for (auto it = PhysicalObjects.begin(); it != PhysicalObjects.end(); it++){
		it->velocity += it->accel;
		it->AngularVelocity = it->AngularVelocity * it->AngularAccel;
		it->AngularVelocity.NormalizeThis();

		it->parentObject->Translate(it->velocity * _deltaTime);
		it->parentObject->Rotate(it->AngularVelocity * _deltaTime);

		//Angular and linear drag goes here
		it->AngularVelocity.w *= (1 - it->angularDrag);
		it->AngularVelocity.NormalizeThis();
		it->velocity *= (1 - it->drag);

		if (Vec3::length(it->velocity) < it->sleepThreshold){
			it->velocity = Vec3::Zero();
		}
	}
}