#pragma once
#include <GameObject.h>
#include <RenderableComponent.h>
#include <Light.h>

class Rigidbody;
class PlayerBall;

class Sun : public GameObject
{
public:
	Sun(Level *, Vec3, std::string);
	~Sun();

	void Update(float) override;

private:
	RenderableComponent * renderer;
	Light * light;
	Rigidbody * rigidBody;
	PlayerBall * player;
	Rigidbody * playerRigidBody;
};

