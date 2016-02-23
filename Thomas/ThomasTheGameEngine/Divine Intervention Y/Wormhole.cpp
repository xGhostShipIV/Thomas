#include "Wormhole.h"

#include "DIY_Level.h"
#include "PlayerBall.h"

Wormhole::Wormhole(Level * level_, Vec3 position_, int layerIndex) : GameObject(level_, position_)
{
	destinationLayer = layerIndex;
	diyLevel = static_cast<DIY_Level *>(level);

	rc = new RenderableComponent("cuboid", "planet1", this);

	ballCaught = false;
}

Layer * Wormhole::getDestinationLayer()
{
	return diyLevel->layers[destinationLayer];
}

void Wormhole::Update(float timeStep_)
{
	if (!player)
		player = static_cast<PlayerBall *>(level->FindGameObjectWithTag("player"));

	GameObject::Update(timeStep_);

	if ((position - player->position).length() < 0.5f)
	{
		if (!ballCaught)
		{
			player->getComponent<Rigidbody>()->velocity = Vec3(0, 0, 0);
			ballCaught = true;
			diyLevel->SetLayerPlane(getDestinationLayer());
		}
	}
	else
	{
		if (ballCaught)
			ballCaught = false;
	}
}