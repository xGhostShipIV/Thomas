#include "LandingScreen.h"
#include <GuiImage.h>
#include <ModelManager.h>
#include <InputHandler.h>

#include <Game.h>
#include "DIY_Level.h"

LandingScreen::LandingScreen()
{
}

void LandingScreen::LoadContent()
{
	Models->loadTexture("LANDING_SCREEN_IMAGE", "Images/Galaxy.png");

	new GuiImage(this, "LANDING_SCREEN_IMAGE", Vec2(), ScreenAnchor::CENTER);

	gui = new Landing_GUI(this);
}

LandingScreen::~LandingScreen()
{
	delete gui;
}

void LandingScreen::LevelUpdate(float timeStep_)
{
	Level::LevelUpdate(timeStep_);

	gui->Update(timeStep_);
}