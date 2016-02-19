#include "WarpGate.h"

#include <RenderableComponent.h>
#include "PlayerBall.h"
#include <Level.h>

WarpGate::WarpGate(Level * level_, Vec3 position_, Quat rotation_) : GameObject(level_, position_)
{
	position = position + Vec3(0, 0.25f, 0);
	rotation = rotation_;

	rc = new RenderableComponent("warpGate", "gateTexture", this);

	Scale(Vec3(0.1, 0.1, 0.1));
}

void WarpGate::Update(float timeStep_)
{
	if (!player)
		player = (PlayerBall *)level->FindGameObjectWithTag("player");

	GameObject::Update(timeStep_);

	if ((position - player->position).length() < 0.75f)
	{
		Rigidbody * rb = player->getComponent<Rigidbody>();

		if (Vec3::dot(forward(), rb->velocity) > 0.5f || Vec3::dot(forward() * -1, rb->velocity) > 0.5f)
		{
			rb->AddForce(rb->velocity.Normalized() * 50.0f);
		}
		else
		{
			rb->velocity = rb->velocity * -1.f;
		}
	}
}