#pragma once

#include <GameObject.h>
#include <RenderableComponent.h>
#include <Rigidbody.h>

#include "Pointer.h"
#include "Slingshot.h"

class PlayerBall : public GameObject
{
public:
	PlayerBall(Level *, Vec3);
	~PlayerBall(){}

	void Update(float timeStep_) override;

	float GetChargePercent();
	bool GetIsChargingStrike();

	void FoulReset();

	Pointer * hand;
private:
	RenderableComponent * renderer;
	Rigidbody * rigidBody; 

	bool chargingStrike;

	const int MAX_FORCE = 150;
	const float CHARGE_PER_SECOND = 100.0f;

	Vec3 positionAtStrike;

	float chargePercent;
	float modifier;
};