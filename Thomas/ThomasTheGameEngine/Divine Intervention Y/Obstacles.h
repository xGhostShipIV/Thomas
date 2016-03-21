#pragma once

#include <GameObject.h>
#include "DIY_Level.h"
#include <PhysicsWorld.h>
#include <RenderableComponent.h>

class PlayerBall;

class Satellite : public GameObject{
private:
	float orbitSpeed;
	Vec3 orbitAxis;
	Planet* planet;
	Rigidbody * rigidBody;
	Generic_RenderableComponent * renderer;

public:
	Satellite(DIY_Level* level_,Planet* planet_, Vec3 starticPos_, Vec3 inPlaneVector_, float orbitSpeed_, std::string modelName_, std::string textureName_);
	~Satellite();

	void Update(float _deltaTime) override;
};

class PopUp : public GameObject
{
public:
	PopUp(Level *, Vec3);
	~PopUp();

	void Update(float) override;
private:
	Generic_RenderableComponent * renderer;
	PlayerBall * player;

	const float UPWARD_FORCE = 150.0f;
};