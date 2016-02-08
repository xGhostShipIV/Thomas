#include "Layer.h"

Layer::Layer(Level * _level, Vec3 _position, std::vector<GameObject *> _objects) : GameObject(_level, _position)
{
	objects = _objects;

	r = new RenderableComponent("cuboid", "layerGrid", this);
	//Rotate(Quat(3.141582654 / 2.0f, Vec3(1, 0, 0)));
	this->Scale(Vec3(5.0, 0.1f, 5));
}


Layer::~Layer()
{
}

void Layer::Render()
{
	GameObject::Render();
}
