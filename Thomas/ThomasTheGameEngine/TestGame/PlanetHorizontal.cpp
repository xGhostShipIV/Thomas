#include "PlanetHorizontal.h"

PlanetHorizontal::PlanetHorizontal(Level * level_, Vec3 position_, std::string textName) : GameObject(level_)
{
	position = position_ + Vec3(0, 0.75f, 0);

	renderer = new RenderableComponent("sphere", textName, this);
}