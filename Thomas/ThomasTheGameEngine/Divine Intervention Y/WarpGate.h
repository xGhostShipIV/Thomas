#pragma once

#include <GameObject.h>

class RenderableComponent;
class PlayerBall;
class Sound;

class WarpGate : public GameObject
{
public:
	WarpGate(Level *, Vec3, Quat);
	~WarpGate(){}

	void Update(float) override;
private:
	RenderableComponent * rc;
	PlayerBall * player;
	Sound * sound;
};