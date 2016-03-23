#include "GalaxyMap.h"
#include "Node.h"

#include <RenderableComponent.h>
#include <Random.h>

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
		std::string levelName = "Level0";

		if (i + 1 < 10)
		{
			levelName += "0" + std::to_string(i + 1);
		}
		else levelName += std::to_string(i + 1);

		levelName += ".xml";

		//Generate a random position
		Vec3 nodePosition = Vec3(cos(Random::box_muller(0, 1)), -0.2f, sin(Random::box_muller(0, 1))).Normalized() * Random::box_muller(0, 25);
		nodePosition.y = -0.2f;

		//Loop to ensure that nodes aren't spawned too close to eachother
		if (i != 0)
		{
			while ((nodePosition - nodes[i - 1]->position).magnitude() < 1.0f)
			{
				nodePosition = Vec3(cos(Random::box_muller(0, 1)), -0.2f, sin(Random::box_muller(0, 1))).Normalized() * Random::box_muller(0, 25);
				nodePosition.y = -0.2f;
			}
		}

		Node * star = new Node(level_, nodePosition, levelName);
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