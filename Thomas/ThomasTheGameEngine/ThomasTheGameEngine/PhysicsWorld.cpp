#include "PhysicsWorld.h"
#include "Rigidbody.h"
#include "Game.h"
#include "Collider.h"
#include <iostream> 

PhysicsWorld * PhysicsWorld::instance;
bool PhysicsWorld::isPhysicsRunning = true;

PhysicsWorld::PhysicsWorld()
{
	worldGravity = Vec3(0, -5.f, 0);
}

float PhysicsWorld::getTimeStep(){
	return lastTimeStep;
}

PhysicsWorld::~PhysicsWorld()
{
}

//point to rotate around, axis of rotation, thing that's rotating, how much to rotate.
void PhysicsWorld::Orbit(Vec3 _point,Vec3 _axis, GameObject* _rotator, float _angle)
{
	if (!isPhysicsRunning)
		return;

	_rotator->Translate((Quat::rotate(Quat(_angle,_axis ), _rotator->position - _point) + _point) - _rotator->position);
}

//Velocity is not changed, will experience strange behaviour
void PhysicsWorld::Orbit(Rigidbody* mover_, GameObject* centre)
{
	if (!isPhysicsRunning)
		return;

	Orbit(centre->position, Vec3::cross(mover_->velocity, mover_->parentObject->position - centre->position), mover_->parentObject, Vec3::length(mover_->velocity) / Vec3::length(mover_->parentObject->position - centre->position));

}

void PhysicsWorld::Impulse(Rigidbody* _first, Rigidbody*_second){
	if (!isPhysicsRunning) { return; }

	if (!_first->isKinematic && !_second->isKinematic) { return; }

	float epsilon = 0.8f; //Change elasticity of collisions


	//Calculating the collision point and normal based on collider types
	Vec3 normal, ColPoint, r1, r2;
	if (_first->col->type == Collider::ColliderType::Sphere && _second->col->type == Collider::ColliderType::Sphere)
	{
		//Sphere-Sphere
		normal = (_first->parentObject->position - _second->parentObject->position).Normalized();
		if (_first->isKinematic && _second->isKinematic)
		{
			ColPoint = Vec3((_second->parentObject->position - _first->parentObject->position) / 2) + _first->parentObject->position;
		}
		else if (_first->isKinematic)
		{
			ColPoint = _second->parentObject->position + normal * static_cast<SphereCollider*>(_second->col)->collisionRadius;
		} 
		else
		{
			ColPoint = _first->parentObject->position - normal * static_cast<SphereCollider*>(_first->col)->collisionRadius;
		}
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

	//More number calculation, independant of collider type
	r1 = ColPoint - (_first->centreOfMass + _first->parentObject->position);
	r2 = ColPoint - (_second->centreOfMass + _second->parentObject->position);

	//Penetration adjustement
	if (_first->isKinematic){
		_first->parentObject->position = ColPoint - r1.Normalized() * static_cast<SphereCollider*>(_first->col)->collisionRadius;
	}
	if (_second->isKinematic){
		_second->parentObject->position = ColPoint - r2.Normalized() * static_cast<SphereCollider*>(_second->col)->collisionRadius;
	}	

	//J Calculation
	float J = Vec3::dot(normal, _first->velocity - _second->velocity) * -1 * (1 + epsilon) /
		(
		(1 / _first->mass) +  (1 / _second->mass) +
		Vec3::dot(normal, Vec3::cross(_first->inertiaTensor.inverse() * Vec3::cross(r1, normal), r1)) +
		Vec3::dot(normal, Vec3::cross(_second->inertiaTensor.inverse() * Vec3::cross(r2, normal),r2))
		);

	//Adjust for kinematics, impulse force includes tangential (friction) and normal impulse forces
	if (!_first->isKinematic || !_second->isKinematic){
		Vec3 gravComp = Vec3::dot(Physics->worldGravity, normal.Normalized()) * normal.Normalized() * Physics->lastTimeStep;
		if (_first->isKinematic){
			_first->accel += (normal * J) / _first->mass;
			_first->accel -= gravComp;
		}
		else if (_second->isKinematic){
			_second->accel += (normal * -1 * J) / _second->mass;
			_second->accel -= gravComp;
		}
	}
	else {
		_first->accel += (normal * J) / _first->mass;
		_second->accel += (normal * -J) / _second->mass;
	}
	/*firstBody->AngularAccel = firstBody->AngularAccel * Quat(-J / 1000.0f, Vec3::cross(r1, normal).Normalized());
	secondBody->AngularAccel = secondBody->AngularAccel * Quat(J / 1000.0f, Vec3::cross(r2, normal).Normalized());*/

}

void PhysicsWorld::Update(float _deltaTime){

	lastTimeStep = _deltaTime;
	 
	if (isPhysicsRunning){
		//Collision Response
		for (auto first = PhysicalObjects.begin(); first != PhysicalObjects.end(); first++){
			if ((*first)->isEnabled)
			for (auto second = std::next(first, 1); second != PhysicalObjects.end(); second++){
				if ((*second)->isEnabled && ((*first)->isKinematic || (*second)->isKinematic))
				{
					if (Collider::isColliding((*first)->col, (*second)->col)){
						PhysicsWorld::Impulse((*first), (*second));
						float dragForce = Vec3::length(worldGravity / 1.5) * 0.4;
						(*first)->AddForce((*first)->velocity.Normalized() * -dragForce);
						(*second)->AddForce((*second)->velocity.Normalized() * -dragForce);
					}
				}
			}
		}

		for (auto it = PhysicalObjects.begin(); it != PhysicalObjects.end(); it++){
			if ((*it)->isEnabled)
			{
				if ((*it)->isKinematic) {
					if ((*it)->gravitas){
						(*it)->AddForce(worldGravity * (*it)->mass * _deltaTime);
					}

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
				}

				(*it)->accel = Vec3::Zero();
				(*it)->AngularAccel = Quat::Identity();

			}

		}
	}
}