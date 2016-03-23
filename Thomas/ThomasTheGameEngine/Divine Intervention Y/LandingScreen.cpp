#include "LandingScreen.h"
#include <GuiImage.h>
#include <ModelManager.h>
#include <InputHandler.h>
#include <RenderableComponent.h>
#include <Ray.h>
#include <../Math/Plane.h>

#include <Game.h>
#include <AudioManager.h>

#include "DIY_Level.h"
#include "Node.h"

LandingScreen::LandingScreen()
{
}

void LandingScreen::LoadContent()
{
	Models->CreateSkybox("skybox", 1000.0f);

	Models->loadTexture("skybox1",		"Images/skyboxUP.png");
	Models->loadTexture("galaxyMap",	"Images/galaxy1.png");

	Audio->loadMusic("menuTheme",		"Sounds/menu.wav");
	Audio->getMusic("menuTheme")->Play();

	/* Set up and position skybox */
	{
		skybox = new GameObject(this);
		new Generic_RenderableComponent(skybox, "skybox", "skybox1");
		skybox->Rotate(Quat(1.5 * M_PI, Vec3(0, 1, 0)));
	}

	//Set string to nothing.
	//Will do a check when play button is clicked
	targetFileName = "";

	galaxyMap = new GalaxyMap(this);

	mainCamera->LookAt(galaxyMap->position);

	gui = new Landing_GUI(this);
}

LandingScreen::~LandingScreen()
{
	delete gui;
}

void LandingScreen::LevelUpdate(float timeStep_)
{
	Level::LevelUpdate(timeStep_);

	if (gui->GetState() == Tranisiton)
	{
		if ((galaxyMap->position - mainCamera->position).length() > 15.f)
		{
			mainCamera->Translate((galaxyMap->position - mainCamera->position).Normalized() * (10 * timeStep_));
			mainCamera->LookAt(galaxyMap->position);
		}
		else
		{
			gui->SetState(Select);
			galaxyMap->SetIsRotating(false);
		}
	}
	else if (gui->GetState() == Select)
	{
		if (Input->isMouseDown(SDL_BUTTON_LEFT))
		{
			for (int i = 0; i < galaxyMap->nodes.size(); i++)
			{
				Ray ray = Ray();
				ray.fromScreen();

				Vec3 rayHitPosition;
				Plane targetPlane = Plane(galaxyMap->nodes[i]->forward(), galaxyMap->nodes[i]->position.magnitude());

				ray.castTo(targetPlane, rayHitPosition);
				if ((galaxyMap->nodes[i]->position - rayHitPosition).magnitude() < 20.0f)
				{
					printf("selected Level\n");
					targetFileName = ((Node *)galaxyMap->nodes[i])->GetFileName();
				}
			}

		}
	}

	gui->Update(timeStep_);
}

std::string LandingScreen::GetTargetFileName()
{
	return targetFileName;
}