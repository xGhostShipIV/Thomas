#include "PlanetVertical.h"

PlanetVertical::PlanetVertical(Level * level_, Vec3 position_, std::string textName) : GameObject(level_)
{
	position = position_ + Vec3(0, 1.5, 0);
	Scale(Vec3(2, 2, 2));

	renderer = new RenderableComponent("sphere", textName, this);
}

void PlanetVertical::Update(float timeStep_)
{
	Rotate(Quat(0.3f * timeStep_, Vec3(0, 1, 0)));
}