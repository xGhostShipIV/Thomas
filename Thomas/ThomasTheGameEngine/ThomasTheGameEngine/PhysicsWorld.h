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
	
	std::vector<Rigidbody> PhysicalObjects;

	Vec3 worldGravity;

	float static Impulse(GameObject*, GameObject*);
	void Update(UINT32);
};

