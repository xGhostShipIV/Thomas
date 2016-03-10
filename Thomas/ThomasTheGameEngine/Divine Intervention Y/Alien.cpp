//Author: Nathan Senter
//Date: 10/03/2016

#include "Alien.h"
#include <Rigidbody.h>

Alien::Alien(Level * level_, Vec3 position_, Swarm * swarm_) : GameObject(level_, position_), swarm(swarm_)
{
	stateMachine.ChangeState(new Attack(this));
	stateMachine.ChangeState(new Idle(this));
}


Alien::~Alien()
{
}

Idle::Idle(void * whoAmI_) : State(whoAmI_){}
Idle::~Idle(){}
void Idle::onEnter(){}
void Idle::onExit(){}

void Idle::Execute()
{
	//Orbit around swarm.position

	//Avoid other ships, or not
}

Attack::Attack(void * whoAmI_) : State(whoAmI_){}
Attack::~Attack(){}
void Attack::onEnter(){}
void Attack::onExit(){}

void Attack::Execute()
{
	//chase player ship and fire at it

	//dont crash into the player ship
}
