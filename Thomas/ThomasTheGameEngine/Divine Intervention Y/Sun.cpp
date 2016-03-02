#include "Sun.h"
#include <Colour.h>
#include <PhysicsWorld.h>
#include <Level.h>
#include <AudioManager.h>

#include "PlayerBall.h"
#include "DIY_Level.h"

Sun::Sun(Level * level_, Vec3 position_, std::string textureName_) : GameObject(level_, position_), ballHitIntoSun(false)
{
	renderer = new RenderableComponent("sphere", textureName_, this);
	renderer->SetEffecctedByLight(false, false, false);

	Scale(Vec3(1.75, 1.75, 1.75));

	light = new Light(this, Colour(800, 800, 800), Light::Point);

	rigidBody = new Rigidbody(this, new SphereCollider(this));
	rigidBody->isKinematic = false;
	static_cast<SphereCollider *>(rigidBody->col)->collisionRadius = 0.75f;
	
	Audio->loadSound("whoosh", "Sounds/firewhoosh.wav");
}


Sun::~Sun()
{
}

void Sun::Update(float timeStep_)
{
	if (!player)
	{
		player = static_cast<PlayerBall *>(level->FindGameObjectWithTag("player"));
		playerRigidBody = player->getComponent<Rigidbody>();
	}

	Rotate(Quat(0.5f * timeStep_, Vec3(0, 1, 0)));

	if (Collider::isColliding(rigidBody->col, playerRigidBody->col))
	{
		DIY_Level * level_ = static_cast<DIY_Level *>(level);

		if (!ballHitIntoSun)
		{
			Audio->getSound("whoosh")->Play();
			ballHitIntoSun = true;
		}

		if (level_->HasObjectives() > 0)
		{
			level_->gui->PlayerTookAStroke();
			player->FoulReset();
		}
		else
			level_->PlayerHasShotBallIntoSun = true;
	}
	else
		ballHitIntoSun = false;
}