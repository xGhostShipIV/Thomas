#include "Sun.h"
#include <Colour.h>
#include <Rigidbody.h>
#include <Level.h>

#include "PlayerBall.h"

Sun::Sun(Level * level_, Vec3 position_, std::string textureName_) : GameObject(level_, position_)
{
	renderer = new RenderableComponent("sphere", textureName_, this);
	renderer->SetEffecctedByLight(false, false, false);

	Scale(Vec3(1.25, 1.25, 1.25));

	light = new Light(this, Colour(80, 80, 80), Light::Point);

	rigidBody = new Rigidbody(this, new SphereCollider(this));
	rigidBody->isKinematic = false;
	rigidBody->CollisionRadius = 0.75f;
}


Sun::~Sun()
{
}

void Sun::Update(float timeStep_)
{
	if (!player)
		level->FindGameObjectWithTag("player");

	Rotate(Quat(3 * timeStep_, Vec3(0, 1, 0)));
}