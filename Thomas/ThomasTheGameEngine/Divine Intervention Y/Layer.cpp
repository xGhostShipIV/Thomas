#include "Layer.h"

Layer::Layer(Level * _level, Vec3 _position, std::vector<GameObject *> _objects) : GameObject(_level, _position)
{
	objects = _objects;

	this->Scale(Vec3(5.0, 0.01f, 5));

	for (int i = 0; i < objects.size(); i++)
	{
		addChild(objects[i]);
	}

	r = new RenderableComponent("cuboid", "layerGrid", this);
	//Rotate(Quat(3.141582654 / 2.0f, Vec3(1, 0, 0)));

	//rigidBody = new Rigidbody(this, new PlaneCollider(this, Vec3(0,1,0)));

	//rigidBody->isKinematic = false;
}


Layer::~Layer()
{
}

void Layer::Render()
{
	GameObject::Render();
}
