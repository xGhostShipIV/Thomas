#include "Planet.h"

Planet::Planet(Level * level_, Vec3 position_, std::string textName) : GameObject(level_)
{
	position = position_;

	Scale(Vec3(2, 2, 2));
	renderer = new Generic_RenderableComponent(this, "sphere", textName);
}

void Planet::Update(float timeStep_)
{
	Rotate(Quat(0.3f * timeStep_, Vec3(0, 1, 0)));
}