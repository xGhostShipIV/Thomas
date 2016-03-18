#pragma once
#include <GameObject.h>
#include "Alien.h"

class PlayerBall;

class Swarm : public GameObject
{
public:
	Swarm(Level *, Vec3);
	~Swarm();

	void Update(float) override;
	std::vector<Alien *> aliens;

private:
	PlayerBall * player;

	const int NUM_ALIENS = 20;
	bool inAttackMode;
};

