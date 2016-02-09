#include "PlayerBall.h"

PlayerBall::PlayerBall(Level * level_, Vec3 position_) : GameObject(level_, position_)
{
	position = position + Vec3(0, 5.f, 0);
	renderer = new RenderableComponent("sphere", "ballSkin", this);
	rigidBody = new Rigidbody(this, new SphereCollider(this));

	Scale(Vec3(0.5f, 0.5f, 0.5f));
	static_cast<SphereCollider *>(rigidBody->col)->collisionRadius = 0.3f;
}

void PlayerBall::Update(float timeStep_)
{
	//All the controls go here
}