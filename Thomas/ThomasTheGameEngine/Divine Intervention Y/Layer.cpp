#include "Layer.h"
#include "DIY_Level.h"
Layer::Layer(Level * _level, Vec3 _position, std::vector<GameObject *> _objects) : GameObject(_level, _position)
{
	objects = _objects;

	DIY_Level * dl = static_cast<DIY_Level *>(_level);

	Scale(Vec3(dl->GetLevelBounds().x, 0.01f, dl->GetLevelBounds().x));

	for (int i = 0; i < objects.size(); i++)
	{
		addChild(objects[i]);
	}

	r = new RenderableComponent("cuboid", "layerGrid", this);
	r->SetEffecctedByLight(false, false, false);
}


Layer::~Layer()
{
}

void Layer::Render()
{
	GameObject::Render();
}
