#include "PlayerBall.h"
#include <InputHandler.h>

#include <Game.h>
#include <iostream>
#include "DIY_Level.h"

PlayerBall::PlayerBall(Level * level_, Vec3 position_) : GameObject(level_, position_)
{
	position = position + Vec3(0, 0.25f, 0);
	renderer = new RenderableComponent("sphere", "ballSkin", this);
	rigidBody = new Rigidbody(this, new SphereCollider(this));

	Scale(Vec3(0.5f, 0.5f, 0.5f));
	static_cast<SphereCollider *>(rigidBody->col)->collisionRadius = 0.3f;

	modifier = 0.5f;
	chargePercent = 0;

	chargingStrike = false;

	hand = new Pointer(level_, position + Vec3(1, 0, 0), this);
}

void PlayerBall::Update(float timeStep_)
{
	//All the controls go here
	if (!((DIY_Level*)GAME->currentLevel)->isPaused)
	{
		if (Input->isKeyDown(SDLK_SPACE))
		{
			if (chargingStrike)
			{

				chargePercent += modifier;

				//std::cout << chargePercent << std::endl;

				if (chargePercent >= 100)
					modifier = -0.5f;
				else if (chargePercent <= 0)
					modifier = 0.5f;
			}
			else
				chargingStrike = true;

		}

		if (!Input->isKeyDown(SDLK_SPACE))
		{
			chargingStrike = false;
			rigidBody->AddForce((position - hand->position).Normalized() * ((MAX_FORCE * (chargePercent / 100.0f)) * timeStep_));
			chargePercent = 0;
			modifier = 0.5f;
		}
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