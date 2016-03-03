#include "ObjectivePlanet.h"
#include <PhysicsWorld.h>
#include <AudioManager.h>
#include <Level.h>

#include"PlayerBall.h"
#include "DIY_Level.h"

ObjectivePlanet::ObjectivePlanet(Level * level_, GameObject * planet_, string texutreName, Orbit_Angle orbitAngle_) : GameObject(level_)
{
	planetToOrbit = planet_;

	renderer = new RenderableComponent("sphere", texutreName, this);

	Scale(Vec3(0.5f, 0.5f, 0.5f));

	rigidBody = new Rigidbody(this, new SphereCollider(this));
	static_cast<SphereCollider *>(rigidBody->col)->collisionRadius = 0.25f;	
	rigidBody->isKinematic = false;
	rigidBody->mass = 25.0f;

	position = planet_->position + Vec3(1.6f, 0, 0);
	rotation = Quat::Identity();

	if (orbitAngle_ == Horizonal)
		orbitAxis = Vec3(0, 1, 0);
	else
		orbitAxis = Vec3(0, 0, 1);

	playerRigidBody = nullptr;

	Audio->loadSound("screams", "Sounds/scream.wav");
	sound = Audio->getSound("screams");
}

ObjectivePlanet::~ObjectivePlanet()
{
}

void ObjectivePlanet::Update(float timeStep_)
{
	if (!playerRigidBody)
	{
		playerRigidBody = static_cast<PlayerBall *>(level->FindGameObjectWithTag("player"))->getComponent<Rigidbody>();
	}

	if (!rigidBody->isKinematic)
	{
		PhysicsWorld::Orbit(planetToOrbit->position, orbitAxis, this, 1 * timeStep_);
		Rotate(Quat(0.5f * timeStep_, Vec3(0.3f, 0.6f, 0.1f)));
	}

	if (playerRigidBody->velocity.length() >= FORCE_REQUIRED_TO_DESTROY
		&& Collider::isColliding(rigidBody->col, playerRigidBody->col))
	{

		if (rigidBody->isKinematic == false)
		{
			sound->Play();
			DIY_Level * level_ = static_cast<DIY_Level *>(level);
			rigidBody->AddForce((position - playerRigidBody->parentObject->position).Normalized() * 100);
			level_->AdjustObjectiveCount(-1);
		}

		rigidBody->isKinematic = true;
	}
}
