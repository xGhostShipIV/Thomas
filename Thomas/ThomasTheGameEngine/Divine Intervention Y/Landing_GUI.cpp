#include "Landing_GUI.h"
#include <ModelManager.h>

#include <Game.h>
#include "DIY_Level.h"

Landing_GUI::Landing_GUI(Level *level_)
{
	Vec2 PlayButtonLocation = Vec2(0, 150);
	Vec2 ExitButtonLocation = PlayButtonLocation + Vec2(0, -300);

	/* BUTTONS */
	{
		Models->loadTexture("LANDING_GUI_PLAY",			"Images/Level GUI/Buttons/Play.png");
		Models->loadTexture("LANDING_GUI_PLAY_PRESSED", "Images/Level GUI/Buttons/PlayPressed.png");
		Models->loadTexture("LANDING_GUI_PLAY_HOVERED", "Images/Level GUI/Buttons/PlayHovered.png");

		Models->loadTexture("LANDING_GUI_EXIT",			"Images/Level GUI/Buttons/Exit.png");
		Models->loadTexture("LANDING_GUI_EXIT_PRESSED", "Images/Level GUI/Buttons/ExitPressed.png");
		Models->loadTexture("LANDING_GUI_EXIT_HOVERED", "Images/Level GUI/Buttons/ExitHovered.png");

		PlayButton = new Button(level_, PlayButtonLocation, "LANDING_GUI_PLAY", "LANDING_GUI_PLAY_PRESSED", "LANDING_GUI_PLAY_HOVERED", ScreenAnchor::CENTER);
		ExitButton = new Button(level_, ExitButtonLocation, "LANDING_GUI_EXIT", "LANDING_GUI_EXIT_PRESSED", "LANDING_GUI_EXIT_HOVERED", ScreenAnchor::CENTER);
	}
}

Landing_GUI::~Landing_GUI()
{
}

void Landing_GUI::Update(float timeStep_)
{
	if (PlayButton->buttonState == ButtonState::PRESSED)
	{
		GAME->LoadLevel(new DIY_Level("testLevel.xml"));
	}
	else if (ExitButton->buttonState == ButtonState::PRESSED)
	{
		GAME->setRunning(false);
	}
}