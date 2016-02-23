#pragma once
#include <GameObject.h>
#include <RenderableComponent.h>
#include <Rigidbody.h>

class Layer :
	public GameObject
{
public:
	Layer(Level *, Vec3 position_, std::vector<GameObject *>);
	~Layer();

	std::vector<GameObject *> objects;

	void Render() override;
private:
	RenderableComponent * r;
	/*Rigidbody * rigidBody;*/
};


