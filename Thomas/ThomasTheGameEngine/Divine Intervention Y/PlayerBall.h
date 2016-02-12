#pragma once

#include <GameObject.h>
#include <RenderableComponent.h>
#include <Rigidbody.h>

#include "Pointer.h"

class PlayerBall : public GameObject
{
public:
	PlayerBall(Level *, Vec3);
	~PlayerBall(){}

	void Update(float timeStep_) override;

	float GetChargePercent();
	bool GetIsChargingStrike();

private:
	RenderableComponent * renderer;
	Rigidbody * rigidBody; 
	Pointer * hand;

	bool chargingStrike;

	const int MAX_FORCE = 50;

	float chargePercent;
	float modifier;
};