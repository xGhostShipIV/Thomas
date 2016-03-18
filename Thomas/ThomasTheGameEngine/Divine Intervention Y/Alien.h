//Author: Nathan Senter
//Date: 10/03/2016

#pragma once

#include <GameObject.h>
#include <RenderableComponent.h>
#include <States.h>

class PlayerBall;
class Swarm;
class Rigidbody;
class Sound;

class Alien : public GameObject
{
	friend class Idle;
	friend class Attack;
public:
	Alien(Level *, Vec3, Swarm *);
	~Alien();

	void Update(float) override;
	void ToggleState();
private:
	Swarm * swarm;
	PlayerBall * player;

	RenderableComponent * renderer;

	StateMachine stateMachine;

	Vec3 velocity;
	Vec3 steeringForce;

	Sound * shootSound;

	bool shouldShoot;

	const float IDLE_DISTANCE = 1.0f;
};

class Idle : public State
{
public:

	Idle(void*);
	~Idle();
	void Execute() override;
	void onEnter() override;
	void onExit() override;

};

class Attack : public State
{
public:
	Attack(void*);
	~Attack();
	void Execute() override;
	void onEnter() override;
	void onExit() override;

};

