#include "SplashScreen.h"
#include <GuiImage.h>
#include <ModelManager.h>
#include <InputHandler.h>

#include <Game.h>
#include "DIY_Level.h"

SplashScreen::SplashScreen()
{
}

void SplashScreen::LoadContent()
{
	Models->loadTexture("SPLASH_SCREEN_IMAGE", "Images/splashscreen.png");

	new GuiImage(this, "SPLASH_SCREEN_IMAGE", Vec2(), ScreenAnchor::CENTER);
}

SplashScreen::~SplashScreen()
{

}

void SplashScreen::LevelUpdate(float timeStep_)
{
	if (Input->isAnyKeyPressed())
	{
		GAME->LoadLevel(new DIY_Level("testLevel.xml"));
	}
}