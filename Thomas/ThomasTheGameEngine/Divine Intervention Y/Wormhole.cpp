#include <AudioManager.h>

#include "Wormhole.h"

#include "DIY_Level.h"
#include "PlayerBall.h"

Wormhole::Wormhole(Level * level_, Vec3 position_, int layerIndex) : GameObject(level_, position_)
{
	destinationLayer = layerIndex;
	diyLevel = static_cast<DIY_Level *>(level);

	rc = new RenderableComponent("wormhole", "wormholeTexture", this);

	ballCaught = false;
	isScalingDown = true;
	drawStyle = DRAW_STYLE::RAINBOW_STYLE;

	initialRotation = (rand() % 366);
	Rotate(Quat(initialRotation * M_PI / 180.0f, Vec3::BasisY()));
	rainbowRand = 0.5f;

	Audio->loadSound("wormhole", "Sounds/wormhole.wav");
	sound = Audio->getSound("wormhole");

}

Layer * Wormhole::getDestinationLayer()
{
	return diyLevel->layers[destinationLayer];
}

void Wormhole::Update(float timeStep_)
{
	rainbowRand += ((rand() % 21) - 10) / 100.0f;
	rainbowRand = rainbowRand > 1 ? 1 : rainbowRand < 0.4f ? 0.4f : rainbowRand;

	scale.z = isScalingDown ? scale.z - 0.1f * timeStep_ : scale.z + 0.1f * timeStep_;
	isScalingDown = isScalingDown ? (scale.z < 0 ? false : true) : (scale.z > 0.7f ? true : false);

	Rotate(Quat(-initialRotation * M_PI / 180.0f, Vec3::BasisY()));
	Rotate(Quat(90 * M_PI / 180.0f * timeStep_, Vec3::BasisZ()));
	Rotate(Quat(initialRotation * M_PI / 180.0f, Vec3::BasisY()));

	if (!player)
		player = static_cast<PlayerBall *>(level->FindGameObjectWithTag("player"));

	GameObject::Update(timeStep_);

	if ((position - player->position).length() < 0.5f)
	{
		if (!ballCaught)
		{
			player->getComponent<Rigidbody>()->velocity = Vec3(0, -0.1f, 0);

			sound->Play();

			ballCaught = true;
			diyLevel->SetLayerPlane(getDestinationLayer());

			//Teleport to layer
			player->position.y = getDestinationLayer()->position.y + 0.5f;
		}
	}
	else
	{
		if (ballCaught)
			ballCaught = false;
	}
}