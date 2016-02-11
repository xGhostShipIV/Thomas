#include "Pointer.h"
#include "PlayerBall.h"

#include <InputHandler.h>
#include <PhysicsWorld.h>
#include"DIY_Level.h"

Pointer::Pointer(Level * level_, Vec3 position_, PlayerBall * player_) : GameObject(level_, position_)
{
	renderer = new RenderableComponent("pointer", "white", this);

	Scale(Vec3(0.07f, 0.07f, 0.07f));

	ball = player_;

	static_cast<DIY_Level *>(level)->layerContainer->addChild(this);
}


Pointer::~Pointer()
{
}

void Pointer::Update(float timeStep_)
{
	GameObject::Update(timeStep_);

	position.y = ball->position.y;

	if (Input->isKeyDown(SDLK_RIGHT))
	{
		PhysicsWorld::Orbit(ball->position, Vec3(0, 1, 0), this, 8 * timeStep_);
	}
	if (Input->isKeyDown(SDLK_LEFT))
	{
		PhysicsWorld::Orbit(ball->position, Vec3(0, 1, 0), this, -8 * timeStep_);
	}

	LookAt(ball->position);
	Rotate(Quat(3.14159 / 2.0f, Vec3(0, 1, 0)));

	position.y = ball->position.y - 0.1f;
}