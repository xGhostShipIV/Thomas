#include "PlayerBall.h"
#include <InputHandler.h>
#include <AudioManager.h>

#include <Game.h>
#include <iostream>
#include "DIY_Level.h"

PlayerBall::PlayerBall(Level * level_, Vec3 position_) : GameObject(level_, position_)
{
	addTag("player");

	position = position + Vec3(0, 1.f, 0);
	renderer = new RenderableComponent("sphere", "ballSkin", this);
	rigidBody = new Rigidbody(this, new SphereCollider(this));

	rigidBody->mass = 25.0f;
	//rigidBody->sleepThreshold = 0.69f;

	static_cast<SphereCollider *>(rigidBody->col)->collisionRadius = scale.x / 2.0f;

	modifier = CHARGE_PER_SECOND;
	chargePercent = 0;

	chargingStrike = false;

	hand = new Pointer(level_, position + Vec3(2, -1.f, 0), this);

	positionAtStrike = Vec3();

	Audio->loadSound("ballHit", "Sounds/strike.wav");
	hitSound = Audio->getSound("ballHit");
}

void PlayerBall::Update(float timeStep_)
{	
	//All the controls go here
	if (((DIY_Level*)GAME->currentLevel)->levelState == DIY_Level_State::PLAYING && 
		((DIY_Level*)GAME->currentLevel)->playingState == DIY_Level_Playing_State::SHOOTING)
	{
		if (Input->isKeyDown(SDLK_SPACE))
		{
			if (chargingStrike)
			{

				chargePercent += modifier * timeStep_;

				if (chargePercent >= 100)
					modifier = -CHARGE_PER_SECOND;
				else if (chargePercent <= 0)
					modifier = CHARGE_PER_SECOND;
			}
			else
				chargingStrike = true;

		}

		if (Input->isKeyReleased(SDLK_SPACE))
		{
			hitSound->Play();
			chargingStrike = false;
			rigidBody->AddForce((position - hand->position).Normalized() * ((MAX_FORCE * (chargePercent / 100.0f))) + Vec3(0,3,0));
			rigidBody->AngularAccel = rigidBody->AngularAccel * Quat(0.008f, Vec3::cross(Vec3::BasisY(), (position - hand->position).Normalized()));
			chargePercent = 0;
			modifier = CHARGE_PER_SECOND;

			positionAtStrike = position;
		}
	}

	if (position.x > ((DIY_Level*)level)->GetLayerPlane()->position.x + ((DIY_Level*)level)->GetLevelBounds().x
		|| position.x < ((DIY_Level*)level)->GetLayerPlane()->position.x - ((DIY_Level*)level)->GetLevelBounds().x)
	{
		FoulReset();
	}
	if (position.z >((DIY_Level*)level)->GetLayerPlane()->position.z + ((DIY_Level*)level)->GetLevelBounds().x
		|| position.z < ((DIY_Level*)level)->GetLayerPlane()->position.z - ((DIY_Level*)level)->GetLevelBounds().x)
	{
		FoulReset();
	}
}

float PlayerBall::GetChargePercent()
{
	return chargePercent;
}

bool PlayerBall::GetIsChargingStrike()
{
	return chargingStrike;
}

void PlayerBall::FoulReset()
{
	position = positionAtStrike;
	rigidBody->velocity = Vec3::Zero();
}