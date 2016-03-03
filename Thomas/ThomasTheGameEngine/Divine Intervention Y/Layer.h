#pragma once
#include <GameObject.h>
#include <RenderableComponent.h>
#include <Rigidbody.h>

class DIY_Level;

class Layer :
	public GameObject
{
public:
	Layer(Level *, Vec3 position_, std::vector<GameObject *>);
	~Layer();

	std::vector<GameObject *> objects;

	void Update(float) override;
private:
	RenderableComponent * r;
	DIY_Level * dl;
};


