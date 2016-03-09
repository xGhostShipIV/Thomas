#include "Planet.h"
#include "PlayerBall.h"
#include "DIY_Level.h"

#include <Rigidbody.h>
Planet::Planet(Level * level_, Vec3 position_, float scaleFactor_, std::string textName) : GameObject(level_)
{
	Scale(Vec3(scaleFactor_, scaleFactor_, scaleFactor_));

	position = position_ + Vec3(0, 0.5f, 0);


	renderer = new RenderableComponent("sphere", textName, this);

	rigidbody = new Rigidbody(this, new SphereCollider(this));
	((SphereCollider *)rigidbody->col)->collisionRadius = scale.x / 2.0f;
	rigidbody->CollisionRadius = scale.x / 2.0f;
	rigidbody->isKinematic = false;
	rigidbody->mass = 50.0f;
}

void Planet::Update(float timeStep_)
{
	Rotate(Quat(0.3f * timeStep_, Vec3(0, 1, 0)));

	//Instantiate Player
	if (!player)
	{
		player = (PlayerBall*)level->FindGameObjectWithTag("player");
	}

	//Check Victory conditions
	if (Collider::isColliding(rigidbody->col, player->getComponent<Rigidbody>()->col))
	{
		DIY_Level * level_ = ((DIY_Level *)level);

		if (level_->GetLayerPlane()->GetIndex() == 0)
		{
			level_->PlayerHasShotBallIntoSun = true;
		}
	}
}