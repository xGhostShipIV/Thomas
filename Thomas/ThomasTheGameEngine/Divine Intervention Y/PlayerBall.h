#pragma once

#include <GameObject.h>
#include <RenderableComponent.h>
#include <Rigidbody.h>

class PlayerBall : public GameObject
{
public:
	PlayerBall(Level *, Vec3);
	~PlayerBall(){}

	void Update(float timeStep_) override;

private:
	RenderableComponent * renderer;
	Rigidbody * rigidBody; 
};