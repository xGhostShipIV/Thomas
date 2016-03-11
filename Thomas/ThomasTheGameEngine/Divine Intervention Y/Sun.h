#pragma once
#include <GameObject.h>
#include <RenderableComponent.h>
#include <Light.h>

class Rigidbody;
class PlayerBall;

class Sun : public GameObject
{
public:
	Sun(Level * level_, Vec3 position_, float radius_);
	~Sun();

	void Update(float) override;

private:
	Sun_RenderableComponent * renderer;
	Light * light;
	Rigidbody * rigidBody;
	PlayerBall * player;
	Rigidbody * playerRigidBody;
	bool ballHitIntoSun;
	const float INTENSITY_INCREMENT = 0.1f, MINIMUM_INTENSITY = 0.4f, MAXIMUM_INTENSITY = 0.7f;
};

