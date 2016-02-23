#include "ObjectivePlanet.h"
#include <PhysicsWorld.h>

ObjectivePlanet::ObjectivePlanet(Level * level_, GameObject * planet_, string texutreName, Orbit_Angle orbitAngle_) : GameObject(level_)
{
	planetToOrbit = planet_;

	renderer = new RenderableComponent("sphere", texutreName, this);

	Scale(Vec3(0.25f, 0.25f, 0.25f));

	rigidBody = new Rigidbody(this, new SphereCollider(this));
	rigidBody->CollisionRadius = 0.25f;
	rigidBody->isKinematic = false;
	rigidBody->gravitas = false;

	position = planet_->position + Vec3(0.8f, 0, 0);
	rotation = Quat::Identity();

	if (orbitAngle_ == Horizonal)
		orbitAxis = Vec3(0, 1, 0);
	else
		orbitAxis = Vec3(0, 0, 1);
}

ObjectivePlanet::~ObjectivePlanet()
{
}

void ObjectivePlanet::Update(float timeStep_)
{
	if (!rigidBody->isAwake())
	{
		PhysicsWorld::Orbit(planetToOrbit->position, orbitAxis, this, 1 * timeStep_);
		Rotate(Quat(0.5f * timeStep_, Vec3(0.3f, 0.6f, 0.1f)));
	}
}
