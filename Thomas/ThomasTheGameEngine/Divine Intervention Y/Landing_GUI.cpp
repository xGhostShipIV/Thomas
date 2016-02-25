#include "Landing_GUI.h"
#include <ModelManager.h>

#include <Game.h>
#include "DIY_Level.h"
#include <InputHandler.h>

Landing_GUI::Landing_GUI(Level *level_) : isInstructionsShown(false), isInputIsClear(false)
{
	Vec2 PlayButtonLocation = Vec2(0, 150);
	Vec2 InstructionsButtonLocation = PlayButtonLocation + Vec2(0, -150);
	Vec2 ExitButtonLocation = InstructionsButtonLocation + Vec2(0, -150);

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


		Models->loadTexture("LANDING_GUI_BLANK",		 "Images/Level GUI/Buttons/Blank.png");
		Models->loadTexture("LANDING_GUI_BLANK_HOVERED", "Images/Level GUI/Buttons/BlankHovered.png");
		FontManager::getInstance()->GenerateFont("LANDING_GUI_FONT", 45, "Font/ostrich-regular.ttf");

		InstructionsButton = new TextButton(level_, InstructionsButtonLocation, "Instructions", FontManager::getInstance()->GetFont("LANDING_GUI_FONT"),
			"LANDING_GUI_BLANK", "LANDING_GUI_BLANK_HOVERED", ScreenAnchor::CENTER, Colour::Yellow(), Colour::Lime());
	}

	/* GUI IMAGE*/
	{
		Models->loadTexture("LANDING_GUI_INSTRUCTIONS", "Images/Level GUI/Instructions_0.png");
		InstructionsImage = new GuiImage(level_, "LANDING_GUI_INSTRUCTIONS", Vec2(), ScreenAnchor::CENTER);
		InstructionsImage->Hide();
	}
}

Landing_GUI::~Landing_GUI()
{
}

void Landing_GUI::Update(float timeStep_)
{
	if (!isInputIsClear)
		isInputIsClear = !InputController::getInstance()->isAnyKeyPressed();
	else if (!isInstructionsShown)
	{
		if (PlayButton->buttonState == ButtonState::PRESSED)
		{
			GAME->LoadLevel(new DIY_Level("testLevel.xml"));
		}
		else if (ExitButton->buttonState == ButtonState::PRESSED)
		{
			GAME->setRunning(false);
		}
		else if (InstructionsButton->buttonState == ButtonState::PRESSED)
		{
			isInstructionsShown = true;
			isInputIsClear = false;
			InstructionsImage->Show();
		}
	}
	else
	{
		if (!isInputIsClear)
			isInputIsClear = !InputController::getInstance()->isAnyKeyPressed();
		else if (InputController::getInstance()->isAnyKeyPressed())
		{
			isInstructionsShown = false;
			InstructionsImage->Hide();
			isInputIsClear = false;
		}
	}
}