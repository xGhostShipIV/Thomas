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
}


Layer::~Layer()
{
}

void Layer::Render()
{
	GameObject::Render();
}
