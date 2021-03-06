#include "GalaxyMap.h"
#include "Node.h"

#include <RenderableComponent.h>
#include <Random.h>
#include <ModelManager.h>
#include <dependencies\TinyXML\tinyxml2.h>

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

	float radius_ = 1.3f;
	Models->loadModel("core", "Models/turboSphere.obj", true);
	core = new GameObject(level_, Vec3());
	renderer = new Sun_RenderableComponent(core, "core");
	renderer->intensity = 1.0f;
	renderer->coreColour = Colour(1.0f, 1, 1, 0) * 2;
	renderer->rippleColour = Colour(8.0f, 0.4f, 0, 0);
	core->Scale(Vec3::One() * radius_);

	glow = new GameObject(level_, core->position);
	glow->Scale(Vec3::One() * radius_ * 1.34f);
	glow_renderer = new Glow_RenderableComponent(glow, "core");
	glow_renderer->glowColour = Colour(1.0f, 0.8f, 0.8f, 0) * 1.0f;
	core->addChild(glow);

	addChild(core);

	int i = 0;
	bool levelExists = true;
	while (levelExists)
	{
		std::string levelName = "Level0";

		if (i + 1 < 10)
		{
			levelName += "0" + std::to_string(i + 1);
		}
		else levelName += std::to_string(i + 1);

		levelName += ".xml";

		tinyxml2::XMLDocument doc;
		if (doc.LoadFile(levelName.c_str()) == tinyxml2::XML_NO_ERROR)
		{
			//Generate a random position
			float r = Random::box_muller(5.5, 1.5);
			float theta = Random::box_muller(M_PI, M_PI);

			Vec3 nodePosition = Vec3(r * cos(theta), -0.2f, r * sin(theta));

			//Vec3 nodePosition = Vec3(cos(Random::box_muller(0, 1)), -0.2f, sin(Random::box_muller(0, 1))).Normalized() * Random::box_muller(0, 25.0f / 2.0f);
			//nodePosition.y = -0.2f;

			//Loop to ensure that nodes aren't spawned too close to eachother
			if (i != 0)
			{
				while ((nodePosition - nodes[i - 1]->position).magnitude() < 1.0f)
				{
					float r = Random::box_muller(10, 10) + 5;
					float theta = Random::box_muller(M_PI, M_PI);

					Vec3 nodePosition = Vec3(r * cos(theta), -0.2f, r * sin(theta));
				}
			}

			Node * star = new Node(level_, nodePosition, levelName);
			nodes.push_back(star);
			addChild(nodes.back());

			i++;
		}
		else
		{
			levelExists = false;
		}		
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
	if (isRotating) //FAST
	{
		Rotate(Quat(0.25f * timeStep_, up()));
	}
	else
		Rotate(Quat(0.125f * timeStep_, up()));
}