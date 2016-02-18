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

float PhysicsWorld::getTimeStep(){
	return lastTimeStep;
}

PhysicsWorld::~PhysicsWorld()
{
}

void PhysicsWorld::Orbit(Vec3 _point,Vec3 _axis, GameObject* _rotator, float _angle){
	_rotator->Translate((Quat::rotate(Quat(_angle,_axis ), _rotator->position - _point) + _point) - _rotator->position);
}

//Not tested, will be tested in testing area with actual planet movements
//Velocity is not changed, will experience strange behaviour
void PhysicsWorld::Orbit(Rigidbody* mover_, GameObject* centre){
	Orbit(centre->position, Vec3::cross(mover_->velocity, mover_->parentObject->position - centre->position), mover_->parentObject, Vec3::length(mover_->velocity) / Vec3::length(mover_->parentObject->position - centre->position));
	//rotate velocity vector to match new heading
	//mover_->velocity = Quat::rotate(, mover_->velocity);

}

void PhysicsWorld::Impulse(GameObject* _first, GameObject*_second){

	Rigidbody* firstBody = _first->getComponent<Rigidbody>();
	Rigidbody* secondBody = _second->getComponent<Rigidbody>();
	float epsilon = 0.9f; //Perfectly elastic collisions for now

	//Populate the variables for the impulse equation
	Vec3 normal, ColPoint, r1, r2;
	if (_first->getComponent<Collider>()->type == Collider::ColliderType::Sphere && _second->getComponent<Collider>()->type == Collider::ColliderType::Sphere)
	{
		//Sphere-Sphere
		normal = (_first->position - _second->position).Normalized();
		ColPoint = Vec3((_second->position - _first->position) / 2) + _first->position;
	}
	else if ((_first->getComponent<Collider>()->type == Collider::ColliderType::Sphere || _second->getComponent<Collider>()->type == Collider::ColliderType::Sphere)){
		//Sphere-Plane
		if ((_first->getComponent<Collider>()->type == Collider::ColliderType::BoundedPlane)){
			normal = static_cast<PlaneCollider*>(_first->getComponent<Collider>())->plane.normal.Normalized();
			ColPoint = _second->position - static_cast<PlaneCollider*>(_first->getComponent<Collider>())->plane.normal.Normalized() * static_cast<PlaneCollider*>(_first->getComponent<Collider>())->plane.DistanceToPoint(_second->position);
		}
		else if ((_second->getComponent<Collider>()->type == Collider::ColliderType::BoundedPlane)) {
			normal = static_cast<PlaneCollider*>(_second->getComponent<Collider>())->plane.normal.Normalized();
			ColPoint = _first->position - static_cast<PlaneCollider*>(_second->getComponent<Collider>())->plane.normal.Normalized() * static_cast<PlaneCollider*>(_second->getComponent<Collider>())->plane.DistanceToPoint(_first->position);
		}		
	}

	r1 = ColPoint - (firstBody->centreOfMass + _first->position);
	r2 = ColPoint - (secondBody->centreOfMass + _second->position);

	float J = Vec3::dot(normal, firstBody->velocity - secondBody->velocity) * -1 * (1 + epsilon) /
		(
		(1 / firstBody->mass) +  (1 / secondBody->mass) +
		Vec3::dot(normal, Vec3::cross(firstBody->inertiaTensor.inverse() * Vec3::cross(r1, normal),r1)) +
		Vec3::dot(normal, Vec3::cross(secondBody->inertiaTensor.inverse() * Vec3::cross(r2, normal),r2))
		);

	if (!firstBody->isKinematic || !secondBody->isKinematic){
		Vec3 gravComp = Vec3::dot(PhysicsWorld::getInstance()->worldGravity, normal.Normalized()) * normal.Normalized() * PhysicsWorld::getInstance()->lastTimeStep;
		if (firstBody->isKinematic){
			firstBody->accel += normal * 2 * J / firstBody->mass;
			firstBody->accel += gravComp;
		}
		else if (secondBody->isKinematic){
			secondBody->accel += normal * -2 * J / secondBody->mass;
			secondBody->accel -= gravComp;
		}
	}
	else {
		firstBody->accel += normal * J / firstBody->mass;
		secondBody->accel += normal * -J / secondBody->mass;
	}

	if (firstBody->isKinematic){
		firstBody->parentObject->position = ColPoint - r1.Normalized() * static_cast<SphereCollider*>(_first->getComponent<Collider>())->collisionRadius;
	}
	if (secondBody->isKinematic){
		secondBody->parentObject->position = ColPoint - r2.Normalized() * static_cast<SphereCollider*>(_second->getComponent<Collider>())->collisionRadius;
	}

	/*firstBody->AngularAccel = firstBody->AngularAccel * Quat(-J / 1000.0f, Vec3::cross(r1, normal).Normalized());
	secondBody->AngularAccel = secondBody->AngularAccel * Quat(J / 1000.0f, Vec3::cross(r2, normal).Normalized());*/

}

void PhysicsWorld::Update(float _deltaTime){

	lastTimeStep = _deltaTime;
	 
	//Collision Response
	for (auto first = PhysicalObjects.begin(); first != PhysicalObjects.end(); first++){
		for (auto second = std::next(first, 1); second != PhysicalObjects.end(); second++){
			if (Collider::isColliding((*first)->col, (*second)->col)){
				PhysicsWorld::Impulse((*first)->parentObject, (*second)->parentObject);
			}
		}
	}

	for (auto it = PhysicalObjects.begin(); it != PhysicalObjects.end(); it++){
		if ((*it)->gravitas){
			(*it)->AddForce(worldGravity * (*it)->mass * _deltaTime);
		}

		if ((*it)->isKinematic) {
			//Angular and linear drag goes here
			//1/2 rho v^2 Cd A
			float dragForce = 0.5f * 0.2 * Vec3::length((*it)->velocity) * Vec3::length((*it)->velocity) * 0.5f * (M_PI * (*it)->CollisionRadius * (*it)->CollisionRadius);
			(*it)->AddForce((*it)->velocity * -dragForce * _deltaTime);

			//Lift
			//pi r ^ 3 w v rho
			float liftForce = M_PI * ((*it)->CollisionRadius * (*it)->CollisionRadius * (*it)->CollisionRadius) * (acos((*it)->AngularVelocity.w) * 2) * Vec3::length((*it)->velocity * 0.2f);
			Vec3 lifeDir = Vec3::cross((*it)->velocity, (*it)->AngularVelocity.vector);
			//(*it)->AddForce(lifeDir * liftForce * _deltaTime);

			(*it)->velocity += ((*it)->accel);
			(*it)->AngularVelocity = (*it)->AngularVelocity * (*it)->AngularAccel;

			(*it)->parentObject->Translate((*it)->velocity * _deltaTime);
			(*it)->parentObject->Rotate((*it)->AngularVelocity.NormalizeThis() * _deltaTime);

			(*it)->accel = Vec3::Zero();
			(*it)->AngularAccel = Quat::Identity();

			//Sleep velocities are here
			if (Vec3::length((*it)->velocity) < (*it)->sleepThreshold){
				(*it)->velocity = Vec3::Zero();
			}
		}
	}
}