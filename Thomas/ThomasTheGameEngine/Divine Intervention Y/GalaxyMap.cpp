#include "GalaxyMap.h"
#include "AmbientStar.h"

#include <RenderableComponent.h>

GalaxyMap::GalaxyMap(Level * level_) : GameObject(level_)
{
	plane1 = new GameObject(level_, Vec3(0, 0, 0));
	plane1->Rotate(Quat(3.14159f / 2.f, Vec3(1, 0, 0)));

	plane2 = new GameObject(level_, Vec3(0, 0, 0));
	plane2->Rotate(Quat(-(3.14159f / 2.f), Vec3(1, 0, 0)));

	new Generic_RenderableComponent(plane1, "plane", "galaxyMap", 3.0f);
	new Generic_RenderableComponent(plane2, "plane", "galaxyMap", 3.0f);

	addChild(plane1);
	addChild(plane2);

	//Have to scale the galaxy before adding nodes. For some reason
	//star wont scale with parent
	Scale(Vec3(25, 25, 25));

	for (int i = 0; i < NUMBER_OF_NODES; i++)
	{
		//Hard coding position for now cause I dont want to deal with random
		AmbientStar * star = new AmbientStar(level_, Vec3(5.f, -0.2f, -2.f));
		nodes.push_back(star);
		addChild(nodes.back());
	}

	//Get a nice looking rotation on it
	Rotate(Quat((3.14159f / 1.5f), Vec3(1, 0, 0)));

	Translate(Vec3(0, -5.f, 50));

	isRotating = true;

}


GalaxyMap::~GalaxyMap()
{
}

bool GalaxyMap::IsRotating()
{
	return isRotating;
}

void GalaxyMap::SetIsRotating(bool isRotating_)
{
	isRotating = isRotating_;
}

void GalaxyMap::Update(float timeStep_)
{
	if (isRotating)
	{
		Rotate(Quat(0.25f * timeStep_, up()));
	}
}