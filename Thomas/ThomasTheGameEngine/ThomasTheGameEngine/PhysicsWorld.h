#pragma once
#include "GameObject.h"
#include "Rigidbody.h"

class PhysicsWorld
{
	PhysicsWorld();
	~PhysicsWorld();
public:
	static PhysicsWorld * instance;
	static PhysicsWorld * getInstance(){
		if (!instance)instance = new PhysicsWorld();
		return instance;
	}
	
	std::vector<Rigidbody*> PhysicalObjects;

	//Easies to think of in regular gravity units (Newtons or KG * M / S^2) whatever works though earth standard is Vec3(0,-9.8,0)
	Vec3 worldGravity;

	void static Impulse(GameObject*, GameObject*);
	void Update(float);
};

