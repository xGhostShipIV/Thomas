#include "PhysicsWorld.h"
#include "Rigidbody.h"
#include "Game.h"
#include "Collider.h"
#include <iostream> 

PhysicsWorld * PhysicsWorld::instance;

PhysicsWorld::PhysicsWorld()
{
	worldGravity = Vec3(0, -3.f, 0);
	isPhysicsRunning = true;
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

void PhysicsWorld::Impulse(Rigidbody* _first, Rigidbody*_second){

	//Rigidbody* firstBody = _first->getComponent<Rigidbody>();
	//Rigidbody* secondBody = _second->getComponent<Rigidbody>();
	float epsilon = 0.9f; //Perfectly elastic collisions for now

	//Populate the variables for the impulse equation
	//Vec3 normal, ColPoint, r1, r2;
	//if (_first->getComponent<Collider>()->type == Collider::ColliderType::Sphere && _second->getComponent<Collider>()->type == Collider::ColliderType::Sphere)
	//{
	//	//Sphere-Sphere
	//	normal = (_first->position - _second->position).Normalized();
	//	ColPoint = Vec3((_second->position - _first->position) / 2) + _first->position;
	//}
	//else if ((_first->getComponent<Collider>()->type == Collider::ColliderType::Sphere || _second->getComponent<Collider>()->type == Collider::ColliderType::Sphere)){
	//	//Sphere-Plane
	//	if ((_first->getComponent<Collider>()->type == Collider::ColliderType::BoundedPlane)){
	//		normal = static_cast<PlaneCollider*>(_first->getComponent<Collider>())->plane.normal.Normalized();
	//		ColPoint = _second->position - static_cast<PlaneCollider*>(_first->getComponent<Collider>())->plane.normal.Normalized() * static_cast<PlaneCollider*>(_first->getComponent<Collider>())->plane.DistanceToPoint(_second->position);
	//	}
	//	else if ((_second->getComponent<Collider>()->type == Collider::ColliderType::BoundedPlane)) {
	//		normal = static_cast<PlaneCollider*>(_second->getComponent<Collider>())->plane.normal.Normalized();
	//		ColPoint = _first->position - static_cast<PlaneCollider*>(_second->getComponent<Collider>())->plane.normal.Normalized() * static_cast<PlaneCollider*>(_second->getComponent<Collider>())->plane.DistanceToPoint(_first->position);
	//	}		
	//}

	//r1 = ColPoint - (firstBody->centreOfMass + _first->position);
	//r2 = ColPoint - (secondBody->centreOfMass + _second->position);

	Vec3 normal, ColPoint, r1, r2;
	if (_first->col->type == Collider::ColliderType::Sphere && _second->col->type == Collider::ColliderType::Sphere)
	{
		//Sphere-Sphere
		normal = (_first->parentObject->position - _second->parentObject->position).Normalized();
		ColPoint = Vec3((_second->parentObject->position - _first->parentObject->position) / 2) + _first->parentObject->position;
	}
	else if ((_first->col->type == Collider::ColliderType::Sphere || _second->col->type == Collider::ColliderType::Sphere)){
		//Sphere-Plane
		if ((_first->col->type == Collider::ColliderType::BoundedPlane)){
			normal = static_cast<PlaneCollider*>(_first->col)->plane.normal.Normalized();
			ColPoint = _second->parentObject->position - static_cast<PlaneCollider*>(_first->col)->plane.normal.Normalized() * static_cast<PlaneCollider*>(_first->col)->plane.DistanceToPoint(_second->parentObject->position);
		}
		else if ((_second->col->type == Collider::ColliderType::BoundedPlane)) {
			normal = static_cast<PlaneCollider*>(_second->col)->plane.normal.Normalized();
			ColPoint = _first->parentObject->position - static_cast<PlaneCollider*>(_second->col)->plane.normal.Normalized() * static_cast<PlaneCollider*>(_second->col)->plane.DistanceToPoint(_first->parentObject->position);
		}
	}

	r1 = ColPoint - (_first->centreOfMass + _first->parentObject->position);
	r2 = ColPoint - (_second->centreOfMass + _second->parentObject->position);

	float J = Vec3::dot(normal, _first->velocity - _second->velocity) * -1 * (1 + epsilon) /
		(
		(1 / _first->mass) +  (1 / _second->mass) +
		Vec3::dot(normal, Vec3::cross(_first->inertiaTensor.inverse() * Vec3::cross(r1, normal), r1)) +
		Vec3::dot(normal, Vec3::cross(_second->inertiaTensor.inverse() * Vec3::cross(r2, normal),r2))
		);

	if (!_first->isKinematic || !_second->isKinematic){
		Vec3 gravComp = Vec3::dot(PhysicsWorld::getInstance()->worldGravity, normal.Normalized()) * normal.Normalized() * PhysicsWorld::getInstance()->lastTimeStep;
		if (_first->isKinematic){
			_first->accel += normal * 2 * J / _first->mass;
			_first->accel -= gravComp;
		}
		else if (_second->isKinematic){
			_second->accel += normal * -2 * J / _second->mass;
			_second->accel -= gravComp;
		}
	}
	else {
		_first->accel += normal * J / _first->mass;
		_second->accel += normal * -J / _second->mass;
	}

	if (_first->isKinematic){
		_first->parentObject->position = ColPoint - r1.Normalized() * static_cast<SphereCollider*>(_first->col)->collisionRadius;
	}
	if (_second->isKinematic){
		_second->parentObject->position = ColPoint - r2.Normalized() * static_cast<SphereCollider*>(_second->col)->collisionRadius;
	}

	/*firstBody->AngularAccel = firstBody->AngularAccel * Quat(-J / 1000.0f, Vec3::cross(r1, normal).Normalized());
	secondBody->AngularAccel = secondBody->AngularAccel * Quat(J / 1000.0f, Vec3::cross(r2, normal).Normalized());*/

}

void PhysicsWorld::Update(float _deltaTime){

	lastTimeStep = _deltaTime;
	 
	if (isPhysicsRunning){
		//Collision Response
		for (auto first = PhysicalObjects.begin(); first != PhysicalObjects.end(); first++){
			for (auto second = std::next(first, 1); second != PhysicalObjects.end(); second++){
				if (Collider::isColliding((*first)->col, (*second)->col)){
					PhysicsWorld::Impulse((*first)/*->parentObject*/, (*second)/*->parentObject*/);
				}
			}
		}

		for (auto it = PhysicalObjects.begin(); it != PhysicalObjects.end(); it++){
			if ((*it)->gravitas){
				(*it)->AddForce(worldGravity * (*it)->mass * _deltaTime);
			}

			if ((*it)->isKinematic) {
				//Angular and linear drag goes here
				//Assumes circular cross section for drag
				// 1/2 (density) (velocity * velocity) (drag coefficient) (cross section area) ==> higher velocity
				// 6 * pi * (dynamic viscosity, aka the cheaty number) (radius) (velocity)
				float dragForce;
				if (Vec3::length((*it)->velocity) > 1)
					dragForce = 0.5f * 1.2f * Vec3::length((*it)->velocity) * Vec3::length((*it)->velocity) * 0.5f * (M_PI * (*it)->CollisionRadius * (*it)->CollisionRadius);
				else
					dragForce = 6 * M_PI * 0.2f * (*it)->CollisionRadius * Vec3::length((*it)->velocity);

				(*it)->AddForce((*it)->velocity * -dragForce);

				//Lift
				float liftForce = M_PI * ((*it)->CollisionRadius * (*it)->CollisionRadius * (*it)->CollisionRadius) * (acos((*it)->AngularVelocity.w) * 2) * Vec3::length((*it)->velocity * 0.2f);
				Vec3 lifeDir = Vec3::cross((*it)->velocity, (*it)->AngularVelocity.vector);
				//(*it)->AddForce(lifeDir * liftForce * _deltaTime);

				(*it)->velocity += ((*it)->accel);
				(*it)->AngularVelocity = (*it)->AngularVelocity * (*it)->AngularAccel;

				//Linear motion & sleep
				if ((*it)->velocity.length() > (*it)->sleepThreshold)
				{
					(*it)->parentObject->Translate((*it)->velocity * _deltaTime);
				}
				else 
				{
					(*it)->velocity = Vec3::Zero();
				}
				
				(*it)->parentObject->Rotate((*it)->AngularVelocity.NormalizeThis() * _deltaTime);

				(*it)->accel = Vec3::Zero();
				(*it)->AngularAccel = Quat::Identity();

			}
		}
	}
}