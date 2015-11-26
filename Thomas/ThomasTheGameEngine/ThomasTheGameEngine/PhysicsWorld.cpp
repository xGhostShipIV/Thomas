#include "PhysicsWorld.h"
#include "Rigidbody.h"
#include "Game.h"


PhysicsWorld::PhysicsWorld()
{
	worldGravity = Vec3(0, -9.8f, 0);
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

void PhysicsWorld::Update(float _deltaTime){

	//Collision Response
	for (auto first = PhysicalObjects.begin(); first != PhysicalObjects.end(); first++){
		for (auto second = std::next(first, 1); second != PhysicalObjects.end(); second++){
			if ((*first)->isColliding((*second)->parentObject)){

				float J = PhysicsWorld::Impulse((*first)->parentObject, (*second)->parentObject);

				(*first)->accel += ((*second)->parentObject->position - (*first)->parentObject->position) * J / (*first)->mass;
				(*second)->accel += ((*first)->parentObject->position - (*second)->parentObject->position) * J / (*second)->mass;

				/*(*first)->AngularAccel = (*first)->AngularAccel * Quat::Identity() * ((*first)->inertiaTensor.inverse() * (((*second)->parentObject->position - (*first)->parentObject->position) * J * (*first)->CollisionRadius));
				(*second)->AngularAccel = (*second)->AngularAccel * Quat::Identity() * ((*second)->inertiaTensor.inverse() * (((*first)->parentObject->position - (*second)->parentObject->position) * J * (*second)->CollisionRadius));*/
			}
		}
	}

	for (auto it = PhysicalObjects.begin(); it != PhysicalObjects.end(); it++){
		(*it)->AddForce(worldGravity);

		(*it)->velocity += (*it)->accel * _deltaTime;
		(*it)->AngularVelocity = (*it)->AngularVelocity + (*it)->AngularAccel * _deltaTime;

		(*it)->parentObject->Translate((*it)->velocity * _deltaTime);
		(*it)->parentObject->Rotate(Quat(0,(*it)->AngularVelocity) * _deltaTime);

		//Angular and linear drag goes here
		(*it)->AngularVelocity *= (1 - (*it)->angularDrag);
		(*it)->velocity *= (1 - (*it)->drag);

		if (Vec3::length((*it)->velocity) < (*it)->sleepThreshold){
			(*it)->velocity = Vec3::Zero();
		}

		if (Vec3::length((*it)->AngularVelocity) < (*it)->angularSleep) {
			(*it)->AngularVelocity = Vec3::Zero();
		}
	}
}