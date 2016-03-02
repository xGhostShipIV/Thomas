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
	Wormhole(Level *, Vec3, int);
	~Wormhole(){}

	Layer * getDestinationLayer();
	void Update(float) override;
private:
	RenderableComponent * rc;
	PlayerBall * player;
	DIY_Level * diyLevel;

	int destinationLayer;
	bool ballCaught;

	Sound * sound;
};