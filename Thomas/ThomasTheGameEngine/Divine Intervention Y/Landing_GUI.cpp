#include "Landing_GUI.h"
#include <ModelManager.h>
#include <AudioManager.h>

#include <Game.h>
#include "DIY_Level.h"
#include <InputHandler.h>

Landing_GUI::Landing_GUI(Level *level_) : isInstructionsShown(false), isInputIsClear(false)
{
	Vec2 PlayButtonLocation = Vec2(-500, -150);
	Vec2 InstructionsButtonLocation = PlayButtonLocation + Vec2(0, -75);
	Vec2 ExitButtonLocation = InstructionsButtonLocation + Vec2(0, -75);

	Audio->loadSound("ding", "Sounds/ding.wav");

	/* BUTTONS */
	{
		Models->loadTexture("LANDING_GUI_TITLE",		"Images/logoMaybe.png");
		Models->loadTexture("LANDING_GUI_PLAY",			"Images/Level GUI/Buttons/Play.png");
		Models->loadTexture("LANDING_GUI_PLAY_PRESSED", "Images/Level GUI/Buttons/PlayPressed.png");
		Models->loadTexture("LANDING_GUI_PLAY_HOVERED", "Images/Level GUI/Buttons/PlayHovered.png");

		Models->loadTexture("LANDING_GUI_EXIT",			"Images/Level GUI/Buttons/Exit.png");
		Models->loadTexture("LANDING_GUI_EXIT_PRESSED", "Images/Level GUI/Buttons/ExitPressed.png");
		Models->loadTexture("LANDING_GUI_EXIT_HOVERED", "Images/Level GUI/Buttons/ExitHovered.png");

		PlayButton = new Button(level_, PlayButtonLocation, "LANDING_GUI_PLAY", "LANDING_GUI_PLAY_PRESSED", "LANDING_GUI_PLAY_HOVERED", ScreenAnchor::CENTER);
		ExitButton = new Button(level_, ExitButtonLocation, "LANDING_GUI_EXIT", "LANDING_GUI_EXIT_PRESSED", "LANDING_GUI_EXIT_HOVERED", ScreenAnchor::CENTER);

		PlayButton->Hide();
		ExitButton->Hide();

		Models->loadTexture("LANDING_GUI_BLANK",		 "Images/Level GUI/Buttons/Blank.png");
		Models->loadTexture("LANDING_GUI_BLANK_HOVERED", "Images/Level GUI/Buttons/BlankHovered.png");
		FontManager::getInstance()->GenerateFont("LANDING_GUI_FONT", 45, "Font/ostrich-regular.ttf");

		InstructionsButton = new TextButton(level_, InstructionsButtonLocation, "Instructions", FontManager::getInstance()->GetFont("LANDING_GUI_FONT"),
			"LANDING_GUI_BLANK", "LANDING_GUI_BLANK_HOVERED", ScreenAnchor::CENTER, Colour::Yellow(), Colour::Lime());

		InstructionsButton->Hide();
	}

	//Title Screen
	{
		gameTitle = new GuiImage(level_, "LANDING_GUI_TITLE", Vec2(0, 150), ScreenAnchor::CENTER);
		gameTitle->Scale(Vec3(0.0f, 0.0f, 0.0f));

		pressStart = new Label(level_, "Press Anything To Start...", FontManager::getInstance()->GetFont("LANDING_GUI_FONT"),
			Vec2(0, -250), ScreenAnchor::CENTER, Colour::White());
		pressStart->Hide();

		titleIsShown = false;
	}

	/* GUI IMAGE*/
	{
		Models->loadTexture("LANDING_GUI_INSTRUCTIONS", "Images/Level GUI/Instructions_0.png");
		InstructionsImage = new GuiImage(level_, "LANDING_GUI_INSTRUCTIONS", Vec2(), ScreenAnchor::CENTER);
		InstructionsImage->Hide();
	}

	state = Title;
}

Landing_GUI::~Landing_GUI()
{
}

void Landing_GUI::Update(float timeStep_)
{
	if (state == Title)
	{
		if (!titleIsShown)
		{
			gameTitle->scale = gameTitle->scale + Vec3(0.01f, 0.01f, 0.01f);

			if (gameTitle->scale.x >= 0.5)
			{
				titleIsShown = true;
				pressStart->Show();
			}
		}
		else
		{
			if (Input->isAnyKeyPressed())
			{
				Audio->getSound("ding")->Play();
				state = Tranisiton;
			}
		}
	}
	else if (state == Tranisiton)
	{
			gameTitle->Hide();
			pressStart->Hide();
	}
	else if (state == Select)
	{
		PlayButton->Show();
		ExitButton->Show();
		InstructionsButton->Show();

		if (!isInputIsClear)
			isInputIsClear = !InputController::getInstance()->isAnyKeyPressed();
		else if (!isInstructionsShown)
		{
			if (PlayButton->HasBeenClicked())
			{
				
				Audio->getSound("ding")->Play();
				Audio->getMusic("menuTheme")->Stop();
				GAME->LoadLevel(new DIY_Level("Level002.xml"));
				//GAME->LoadLevel(new DIY_Level("testLevel.xml"));
				//GAME->LoadLevel(new DIY_Level("Level004.xml"));
			}
			else if (ExitButton->HasBeenClicked())
			{
				GAME->setRunning(false);
			}
			else if (InstructionsButton->HasBeenClicked())
			{
				Audio->getSound("ding")->Play();
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
}

Menu_State Landing_GUI::GetState()
{
	return state;
}

void Landing_GUI::SetState(Menu_State newState_)
{
	state = newState_;
}