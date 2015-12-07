#include "PhysicsWorld.h"
#include "Rigidbody.h"
#include "Game.h"
#include "Collider.h"
#include <iostream> 

PhysicsWorld * PhysicsWorld::instance;

PhysicsWorld::PhysicsWorld()
{
	worldGravity = Vec3(0, -3.f, 0);
}


PhysicsWorld::~PhysicsWorld()
{
}

void PhysicsWorld::Orbit(Vec3 _point,Vec3 _axis, GameObject* _rotator, float _angle){
	//std::cout << "Translation angle: " << Quat::rotate(Quat(_angle, _axis), _rotator->position - _point).toString() << std::endl;

	_rotator->Translate((Quat::rotate(Quat(_angle,_axis ), _rotator->position - _point) + _point) - _rotator->position);
}

void PhysicsWorld::Impulse(GameObject* _first, GameObject*_second){

	Rigidbody* firstBody = _first->getComponent<Rigidbody>();
	Rigidbody* secondBody = _second->getComponent<Rigidbody>();
	float epsilon = 1.0f; //Perfectly elastic collisions for now

	//Need some way to determine which type of objects are colliding to change the way the normals and collision points are generated
	Vec3 normal, ColPoint, r1, r2;

	if (true) //This is the generation for sphere-sphere collision
	{
		normal = (_first->position - _second->position).Normalized();
		ColPoint = Vec3((_second->position - _first->position) / 2) + _first->position;
		r1 = ColPoint - (firstBody->centreOfMass + _first->position);
		r2 = ColPoint - (secondBody->centreOfMass + _second->position);
	} else if (false) { //Other forms of collision will go here, 

	}

	float J = Vec3::dot(normal, firstBody->velocity - secondBody->velocity) * -1 * (1 + epsilon) /
		(
		(1 / firstBody->mass) +  (1 / secondBody->mass) +
		Vec3::dot(normal, Vec3::cross(firstBody->inertiaTensor.inverse() * Vec3::cross(r1, normal),r1)) +
		Vec3::dot(normal, Vec3::cross(secondBody->inertiaTensor.inverse() * Vec3::cross(r2, normal),r2))
		);

	firstBody->accel += normal * J / firstBody->mass;
	secondBody->accel += normal * -J / secondBody->mass;
}

void PhysicsWorld::Update(float _deltaTime){

	//Collision Response
	for (auto first = PhysicalObjects.begin(); first != PhysicalObjects.end(); first++){
		for (auto second = std::next(first, 1); second != PhysicalObjects.end(); second++){
			//if ((*first)->isColliding((*second)->parentObject)){// && Vec3::dot((*second)->velocity, (*first)->velocity) < 0){
			if (Collider::isColliding((*first)->col, (*second)->col)){
				PhysicsWorld::Impulse((*first)->parentObject, (*second)->parentObject); //Calculates and applies
			}
		}
	}

	for (auto it = PhysicalObjects.begin(); it != PhysicalObjects.end(); it++){
		if ((*it)->gravitas){
			(*it)->AddForce(worldGravity * (*it)->mass * _deltaTime);
		}

		(*it)->velocity += ((*it)->accel);
		//(*it)->AngularVelocity = (*it)->AngularVelocity + (*it)->AngularAccel * _deltaTime;

		/*if (Vec3::length((*it)->velocity) < (*it)->sleepThreshold){
			(*it)->velocity = Vec3::Zero();
		}*/

		//(*it)->parentObject->Rotate(Quat(0,(*it)->AngularVelocity) * _deltaTime);

		//Angular and linear drag goes here
		//(*it)->AngularVelocity *= (1 - (*it)->angularDrag);
		//(*it)->velocity *= (1 - (*it)->drag);

		// ground 
		if ((*it)->parentObject->position.y <= 0){
			(*it)->velocity.y *= -(1 - (*it)->drag);
			(*it)->parentObject->position.y = 0;
		}

		/*if (Vec3::length((*it)->AngularVelocity) < (*it)->angularSleep) {
			(*it)->AngularVelocity = Vec3::Zero();
		}*/

		(*it)->parentObject->Translate((*it)->velocity * _deltaTime);

		(*it)->accel = Vec3::Zero();
	}
}