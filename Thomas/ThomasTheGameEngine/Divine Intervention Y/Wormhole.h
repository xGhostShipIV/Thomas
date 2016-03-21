//Author : Nathan Senter
//Date : 2/3/2016 (NS)

#pragma once

#include <GameObject.h>
#include <RenderableComponent.h>

class Layer;
class DIY_Level;
class PlayerBall;
class Sound;

class Wormhole : public GameObject
{
public:
	Wormhole(Level *, Vec3, int, Vec3);
	~Wormhole(){}

	Layer * getDestinationLayer();
	void Update(float) override;
private:
	Generic_RenderableComponent * rc;
	PlayerBall * player;
	DIY_Level * diyLevel;

	int initialRotation;
	float yRotation;
	int destinationLayer;
	Vec3 destinationLocation;

	bool ballCaught, isScalingDown;
	Sound * sound;
};