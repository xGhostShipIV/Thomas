#pragma once

#include <GameObject.h>
#include <RenderableComponent.h>

class Rigidbody;
class PlayerBall;

class Planet : public GameObject
{
public:
	Planet(Level *, Vec3, float, std::string textName_);
	~Planet();

	void Update(float) override;
	RenderableComponent * renderer;

private:
	Rigidbody * rigidbody;
	PlayerBall * player;
};