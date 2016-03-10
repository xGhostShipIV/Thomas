#pragma once

#include <GameObject.h>

class Generic_RenderableComponent;
class PlayerBall;
class Sound;

class WarpGate : public GameObject
{
public:
	WarpGate(Level *, Vec3, Quat);
	~WarpGate(){}

	void Update(float) override;
private:
	Generic_RenderableComponent * rc;
	PlayerBall * player;
	Sound * sound;
};