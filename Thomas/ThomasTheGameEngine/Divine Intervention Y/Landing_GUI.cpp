#include "Landing_GUI.h"
#include <ModelManager.h>
#include <AudioManager.h>

#include <Game.h>
#include "DIY_Level.h"
#include <InputHandler.h>
#include "LandingScreen.h"
#include "Node.h"
#include <GameProperties.h>
#include <sstream>

Landing_GUI::Landing_GUI(Level *level_)
{

	Models->loadTexture("LANDING_GUI_DESCRIPTOR", "Images/Level GUI/Buttons/descriptor.png");

	Vec2 OptionsButtonLocation = Vec2(143, 205);
	Vec2 InstructionsButtonLocation = OptionsButtonLocation + Vec2(0, -80);
	Vec2 ExitButtonLocation = InstructionsButtonLocation + Vec2(0, -80);

	landingScreen = ((LandingScreen *)level_);

	Audio->loadSound("ding", "Sounds/ding.wav");
	Audio->loadSound("dong", "Sounds/dong.wav");

	/* BUTTONS */
	{
		Models->loadTexture("LANDING_GUI_TITLE",		"Images/logoMaybe.png");
		/*Models->loadTexture("LANDING_GUI_PLAY",			"Images/Level GUI/Buttons/Play.png");
		Models->loadTexture("LANDING_GUI_PLAY_PRESSED", "Images/Level GUI/Buttons/PlayPressed.png");
		Models->loadTexture("LANDING_GUI_PLAY_HOVERED", "Images/Level GUI/Buttons/PlayHovered.png");

		Models->loadTexture("LANDING_GUI_EXIT",			"Images/Level GUI/Buttons/Exit.png");
		Models->loadTexture("LANDING_GUI_EXIT_PRESSED", "Images/Level GUI/Buttons/ExitPressed.png");
		Models->loadTexture("LANDING_GUI_EXIT_HOVERED", "Images/Level GUI/Buttons/ExitHovered.png");*/
		
		Models->loadTexture("LANDING_GUI_BLANK", "Images/Level GUI/Buttons/Blank.png");
		Models->loadTexture("LANDING_GUI_BLANK_HOVERED", "Images/Level GUI/Buttons/BlankHovered.png");
		FontManager::getInstance()->GenerateFont("LANDING_GUI_FONT", 45, "Font/Aaargh.ttf");

		//PlayButton = new Button(level_, PlayButtonLocation, "LANDING_GUI_PLAY", "LANDING_GUI_PLAY_PRESSED", "LANDING_GUI_PLAY_HOVERED", ScreenAnchor::CENTER);
		//ExitButton = new Button(level_, ExitButtonLocation, "LANDING_GUI_EXIT", "LANDING_GUI_EXIT_PRESSED", "LANDING_GUI_EXIT_HOVERED", ScreenAnchor::CENTER);

		//PlayButton = new SelectButton(level_, PlayButtonLocation, "PLAY", FontManager::getInstance()->GetFont("LANDING_GUI_FONT"), ScreenAnchor::BOTTOM_LEFT);
		
		OptionsButton = new TextButton(level_, OptionsButtonLocation, "Options", FontManager::getInstance()->GetFont("LANDING_GUI_FONT"),
			"LANDING_GUI_BLANK", "LANDING_GUI_BLANK_HOVERED", ScreenAnchor::BOTTOM_LEFT, Colour::Yellow(), Colour::Lime());
		
		ExitButton = new TextButton(level_, ExitButtonLocation, "EXIT", FontManager::getInstance()->GetFont("LANDING_GUI_FONT"),
			"LANDING_GUI_BLANK", "LANDING_GUI_BLANK_HOVERED", ScreenAnchor::BOTTOM_LEFT, Colour::Yellow(), Colour::Lime());

		InstructionsButton = new TextButton(level_, InstructionsButtonLocation, "Instructions", FontManager::getInstance()->GetFont("LANDING_GUI_FONT"),
			"LANDING_GUI_BLANK", "LANDING_GUI_BLANK_HOVERED", ScreenAnchor::BOTTOM_LEFT, Colour::Yellow(), Colour::Lime());

		/*detailsLabel = new MultiLineLabel(level_, "Some sort of text. Look Nathan! Look!", 50, FontManager::getInstance()->GetFont("LANDING_GUI_FONT"),
			Vec2(-150, -200), ScreenAnchor::TOP_RIGHT, Colour::White());
		detailsLabel->Hide();*/
	}

	//Title Screen
	{
		gameTitle = new GuiImage(level_, "LANDING_GUI_TITLE", Vec2(0, 150), ScreenAnchor::CENTER);
		gameTitle->Scale(Vec3(0.0f, 0.0f, 0.0f));
		gameTitle->Hide();

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

	levelDescriptor = new Level_Descriptor(level_);
	
	/* OPTIONS */
	{
		FontManager::getInstance()->GenerateFont("LANDING_GUI_FONT_OPTIONS_LARGE", 45, "Font/Aaargh.ttf");
		FontManager::getInstance()->GenerateFont("LANDING_GUI_FONT_OPTIONS_SMALL", 25, "Font/Aaargh.ttf");

		Vec2 optionSpacing = Vec2(200, -75);

		Vec2 title_location = Vec2(0, -100);
		Vec2 fullscreenOption_Location = title_location + Vec2(-optionSpacing.x, optionSpacing.y);
		Vec2 resolutionOption_Location = fullscreenOption_Location + Vec2(0, optionSpacing.y);
		Vec2 mainSoundVolumeOption_Location = resolutionOption_Location + Vec2(0, optionSpacing.y);
		Vec2 musicVolumeOption_Location = mainSoundVolumeOption_Location + Vec2(0, optionSpacing.y);
		Vec2 soundFXVolumeOption_Location = musicVolumeOption_Location + Vec2(0, optionSpacing.y);

		optionsTitle = new Label(level_, "OPTIONS", FontManager::getInstance()->GetFont("LANDING_GUI_FONT_OPTIONS_LARGE"), title_location, ScreenAnchor::TOP_CENTER, Colour::Yellow());
		fullscreenOption = new Label(level_, "Fullscreen", FontManager::getInstance()->GetFont("LANDING_GUI_FONT_OPTIONS_SMALL"), fullscreenOption_Location, ScreenAnchor::TOP_CENTER, Colour::Yellow());
		resolutionOption = new Label(level_, "Resolution", FontManager::getInstance()->GetFont("LANDING_GUI_FONT_OPTIONS_SMALL"), resolutionOption_Location, ScreenAnchor::TOP_CENTER, Colour::Yellow());
		mainSoundVolumeOption = new Label(level_, "Main Volume", FontManager::getInstance()->GetFont("LANDING_GUI_FONT_OPTIONS_SMALL"), mainSoundVolumeOption_Location, ScreenAnchor::TOP_CENTER, Colour::Yellow());
		musicVolumeOption = new Label(level_, "Music Volume", FontManager::getInstance()->GetFont("LANDING_GUI_FONT_OPTIONS_SMALL"), musicVolumeOption_Location, ScreenAnchor::TOP_CENTER, Colour::Yellow());
		soundFXVolumeOption = new Label(level_, "Sound Effect Volume", FontManager::getInstance()->GetFont("LANDING_GUI_FONT_OPTIONS_SMALL"), soundFXVolumeOption_Location, ScreenAnchor::TOP_CENTER, Colour::Yellow());
		
		fullscreenButton = new TextButton(level_, fullscreenOption_Location + Vec2(optionSpacing.x * 2, 0), "???", FontManager::getInstance()->GetFont("LANDING_GUI_FONT_OPTIONS_LARGE"),
			"LANDING_GUI_BLANK", "LANDING_GUI_BLANK_HOVERED", ScreenAnchor::TOP_CENTER, Colour::Yellow());
		fullscreenButton->Scale(Vec3(25/45.0f, 25/45.0f, 1));
		
		Models->loadTexture("LANDING_GUI_LEFT",			 "Images/Level GUI/Buttons/left_arrow.png");
		Models->loadTexture("LANDING_GUI_LEFT_PRESSED",  "Images/Level GUI/Buttons/left_arrow_pressed.png");
		Models->loadTexture("LANDING_GUI_RIGHT",		 "Images/Level GUI/Buttons/right_arrow.png");
		Models->loadTexture("LANDING_GUI_RIGHT_PRESSED", "Images/Level GUI/Buttons/right_arrow_pressed.png");

		float arrow_button_spacing = 120;
		Vec2 currentResolutionLabel_location = resolutionOption_Location + Vec2(optionSpacing.x * 2, 0);
		Vec2 less_resolutionButton_location = currentResolutionLabel_location + Vec2(-arrow_button_spacing, 0);
		Vec2 more_resolutionButton_location = currentResolutionLabel_location + Vec2(arrow_button_spacing, 0);

		less_resolutionButton = new Button(level_, less_resolutionButton_location, "LANDING_GUI_LEFT", "LANDING_GUI_LEFT_PRESSED", "LANDING_GUI_LEFT", ScreenAnchor::TOP_CENTER);
		currentResolutionLabel = new Label(level_, "1280x720?", FontManager::getInstance()->GetFont("LANDING_GUI_FONT_OPTIONS_SMALL"), currentResolutionLabel_location, ScreenAnchor::TOP_CENTER, Colour::Yellow());
		more_resolutionButton = new Button(level_, more_resolutionButton_location, "LANDING_GUI_RIGHT", "LANDING_GUI_RIGHT_PRESSED", "LANDING_GUI_RIGHT", ScreenAnchor::TOP_CENTER);

		less_mainSoundVolumeButton = new Button(level_, Vec2(less_resolutionButton_location.x, mainSoundVolumeOption_Location.y), "LANDING_GUI_LEFT", "LANDING_GUI_LEFT_PRESSED", "LANDING_GUI_LEFT", ScreenAnchor::TOP_CENTER);
		currentMainSoundVolumeLabel = new Label(level_, "?8?", FontManager::getInstance()->GetFont("LANDING_GUI_FONT_OPTIONS_SMALL"), mainSoundVolumeOption_Location + Vec2(optionSpacing.x * 2, 0), ScreenAnchor::TOP_CENTER, Colour::Yellow());
		more_mainSoundVolumeButton = new Button(level_, Vec2(more_resolutionButton_location.x, mainSoundVolumeOption_Location.y), "LANDING_GUI_RIGHT", "LANDING_GUI_RIGHT_PRESSED", "LANDING_GUI_RIGHT", ScreenAnchor::TOP_CENTER);

		less_musicVolumeButton = new Button(level_, Vec2(less_resolutionButton_location.x, musicVolumeOption_Location.y), "LANDING_GUI_LEFT", "LANDING_GUI_LEFT_PRESSED", "LANDING_GUI_LEFT", ScreenAnchor::TOP_CENTER);
		currentMusicVolumeLabel = new Label(level_, "?8?", FontManager::getInstance()->GetFont("LANDING_GUI_FONT_OPTIONS_SMALL"), musicVolumeOption_Location + Vec2(optionSpacing.x * 2, 0), ScreenAnchor::TOP_CENTER, Colour::Yellow());
		more_musicVolumeButton = new Button(level_, Vec2(more_resolutionButton_location.x, musicVolumeOption_Location.y), "LANDING_GUI_RIGHT", "LANDING_GUI_RIGHT_PRESSED", "LANDING_GUI_RIGHT", ScreenAnchor::TOP_CENTER);

		less_soundFXVolumeButton = new Button(level_, Vec2(less_resolutionButton_location.x, soundFXVolumeOption_Location.y), "LANDING_GUI_LEFT", "LANDING_GUI_LEFT_PRESSED", "LANDING_GUI_LEFT", ScreenAnchor::TOP_CENTER);
		curentSFXVolumeLabel = new Label(level_, "?8?", FontManager::getInstance()->GetFont("LANDING_GUI_FONT_OPTIONS_SMALL"), soundFXVolumeOption_Location + Vec2(optionSpacing.x * 2, 0), ScreenAnchor::TOP_CENTER, Colour::Yellow());
		more_soundFXVolumeButton = new Button(level_, Vec2(more_resolutionButton_location.x, soundFXVolumeOption_Location.y), "LANDING_GUI_RIGHT", "LANDING_GUI_RIGHT_PRESSED", "LANDING_GUI_RIGHT", ScreenAnchor::TOP_CENTER);

		cancelButton = new TextButton(level_, soundFXVolumeOption_Location + Vec2(0, optionSpacing.y * 2), "Cancel", FontManager::getInstance()->GetFont("LANDING_GUI_FONT_OPTIONS_LARGE"),
			"LANDING_GUI_BLANK", "LANDING_GUI_BLANK_HOVERED", ScreenAnchor::TOP_CENTER, Colour::Yellow());

		applyButton = new TextButton(level_, soundFXVolumeOption_Location + (optionSpacing * 2), "Apply", FontManager::getInstance()->GetFont("LANDING_GUI_FONT_OPTIONS_LARGE"),
			"LANDING_GUI_BLANK", "LANDING_GUI_BLANK_HOVERED", ScreenAnchor::TOP_CENTER, Colour::Yellow());

		HideOptions();
	}
	
	state = Title;
	select_state = Select_Default;
	HideSelectButtons();
}

void Landing_GUI::HideOptions()
{
	optionsTitle->Hide();
	fullscreenOption->Hide();
	resolutionOption->Hide();
	mainSoundVolumeOption->Hide();
	musicVolumeOption->Hide();
	soundFXVolumeOption->Hide();
	fullscreenButton->Hide();
	less_resolutionButton->Hide();
	currentResolutionLabel->Hide();
	more_resolutionButton->Hide();
	less_mainSoundVolumeButton->Hide();
	currentMainSoundVolumeLabel->Hide();
	more_mainSoundVolumeButton->Hide();
	less_musicVolumeButton->Hide();
	currentMusicVolumeLabel->Hide();
	more_musicVolumeButton->Hide();
	less_soundFXVolumeButton->Hide();
	curentSFXVolumeLabel->Hide();
	more_soundFXVolumeButton->Hide();
	cancelButton->Hide();
	applyButton->Hide();
}

void Landing_GUI::GetOptions()
{
	isFullscreen = GameProperties::getInstance()->getVideoProperties()->isFullscreen;
	
	int width = GameProperties::getInstance()->getVideoProperties()->screenWidth;
	if (width >= 1920)
		currentResolution = Resolution::_1920x1080;
	else if (width >= 1600)
		currentResolution = Resolution::_1600x0900;
	else if (width >= 1440)
		currentResolution = Resolution::_1440x0900;
	else if (width >= 1280)
		currentResolution = Resolution::_1280x0720;
	else if (width >= 1024)
		currentResolution = Resolution::_1024x0768;
	else 
		currentResolution = Resolution::_0800x0600;
	
	mainSoundVolume = GameProperties::getInstance()->getAudioProperties()->masterVolume * 100;
	musicVolume = GameProperties::getInstance()->getAudioProperties()->musicVolume * 100;
	soundFXVolume = GameProperties::getInstance()->getAudioProperties()->soundVolume * 100;

	
	//Write values to labels
	if (isFullscreen)
		fullscreenButton->SetText("Fullscreen");
	else
		fullscreenButton->SetText("Windowed");

	//Resolution
	std::stringstream ss;
	ss << GameProperties::getInstance()->getVideoProperties()->screenWidth << "x" << GameProperties::getInstance()->getVideoProperties()->screenHeight;
	currentResolutionLabel->SetText(ss.str());

	ss.str(""); ss << mainSoundVolume;
	currentMainSoundVolumeLabel->SetText(ss.str());

	ss.str(""); ss << musicVolume;
	currentMusicVolumeLabel->SetText(ss.str());

	ss.str(""); ss << soundFXVolume;
	curentSFXVolumeLabel->SetText(ss.str());
}

void Landing_GUI::ShowOptions()
{
	GetOptions();

	optionsTitle->Show();
	fullscreenOption->Show();
	resolutionOption->Show();
	mainSoundVolumeOption->Show();
	musicVolumeOption->Show();
	soundFXVolumeOption->Show();
	fullscreenButton->Show();
	less_resolutionButton->Show();
	currentResolutionLabel->Show();
	more_resolutionButton->Show();
	less_mainSoundVolumeButton->Show();
	currentMainSoundVolumeLabel->Show();
	more_mainSoundVolumeButton->Show();
	less_musicVolumeButton->Show();
	currentMusicVolumeLabel->Show();
	more_musicVolumeButton->Show();
	less_soundFXVolumeButton->Show();
	curentSFXVolumeLabel->Show();
	more_soundFXVolumeButton->Show();
	cancelButton->Show();
	applyButton->Show();
}

void Landing_GUI::ShowSelectButtons()
{
	OptionsButton->Show();
	ExitButton->Show();
	InstructionsButton->Show();
}

void Landing_GUI::HideSelectButtons()
{
	OptionsButton->Hide();
	ExitButton->Hide();
	InstructionsButton->Hide();
}

Landing_GUI::~Landing_GUI()
{
}

//Fixes the wonkyness..
bool firstUpdate = true;

void Landing_GUI::Update(float timeStep_)
{
	if (state == Title)
	{
		if (firstUpdate)
			firstUpdate = false;
		else
			gameTitle->Show();

		if (!titleIsShown)
		{
			gameTitle->scale = gameTitle->scale + Vec3(0.01f, 0.01f, 0.01f);

			if (gameTitle->scale.x >= 0.5 * GAME->GetGUIWidth() / (float)GameProperties::getInstance()->getVideoProperties()->screenWidth)
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
		switch (select_state)
		{
		case Menu_Select_State::Select_Default:

			if (landingScreen->loadingScreen->IsVisible())
				GAME->LoadLevel(new DIY_Level(landingScreen->GetTargetFileName()));

			ShowSelectButtons();
			if (levelDescriptor->DescriptorHasBeenSet())
				levelDescriptor->Show();

			if (levelDescriptor->playButton->HasBeenClicked())
			{
				std::string levelName = landingScreen->GetTargetFileName();

				if (levelName != "")
				{
					Audio->getSound("ding")->Play();
					Audio->getMusic("menuTheme")->Stop();
					landingScreen->loadingScreen->Show();
					//GAME->LoadLevel(new DIY_Level(levelName));
				}
			}
			else if (ExitButton->HasBeenClicked())
			{
				Audio->getSound("dong")->Play();
				GAME->setRunning(false);
			}
			else if (InstructionsButton->HasBeenClicked())
			{
				Audio->getSound("ding")->Play();

				InstructionsImage->Show();
				HideSelectButtons();
				levelDescriptor->Hide();

				select_state = Select_Instructions;
			}
			else if (OptionsButton->HasBeenClicked())
			{
				Audio->getSound("ding")->Play();

				ShowOptions();
				HideSelectButtons();
				levelDescriptor->Hide();

				select_state = Select_Options;
			}
			break;
		case Menu_Select_State::Select_Instructions:
			if (Input->isAnyKeyPressed())
			{
				select_state = Select_Default;
				InstructionsImage->Hide();
			}
			break;
		case Menu_Select_State::Select_Options:
			//FULLSCREEN
			if (fullscreenButton->HasBeenClicked())
			{
				isFullscreen = !isFullscreen;

				if (isFullscreen)
					fullscreenButton->SetText("Fullscreen");
				else
					fullscreenButton->SetText("Windowed");
			}

			//RESOLUTION
			if (more_resolutionButton->HasBeenClicked())
			{
				currentResolution = int(currentResolution) - 1 >= 0 ? Resolution(currentResolution - 1) : currentResolution;
				SetResolutionLabel();
			}
			else if (less_resolutionButton->HasBeenClicked())
			{
				currentResolution = int(currentResolution) + 1 <= 5 ? Resolution(currentResolution + 1) : currentResolution;
				SetResolutionLabel();
			}

			//VOLUME
			//Main
			if (less_mainSoundVolumeButton->HasBeenClicked())
			{
				mainSoundVolume = mainSoundVolume - 10 >= 0 ? mainSoundVolume - 10 : mainSoundVolume;

				std::stringstream ss;
				ss << mainSoundVolume;
				currentMainSoundVolumeLabel->SetText(ss.str());

				Audio->setMainVolume(mainSoundVolume / 100.0f);

				Audio->getSound("dong")->Play();
			}
			else if (more_mainSoundVolumeButton->HasBeenClicked())
			{
				mainSoundVolume = mainSoundVolume + 10 <= 100 ? mainSoundVolume + 10 : mainSoundVolume;

				std::stringstream ss;
				ss << mainSoundVolume;
				currentMainSoundVolumeLabel->SetText(ss.str());

				Audio->setMainVolume(mainSoundVolume / 100.0f);

				Audio->getSound("ding")->Play();
			}
			//Music
			if (less_musicVolumeButton->HasBeenClicked())
			{
				musicVolume = musicVolume - 10 >= 0 ? musicVolume - 10 : musicVolume;

				std::stringstream ss;
				ss << musicVolume;
				currentMusicVolumeLabel->SetText(ss.str());

				Audio->setMusicVolume(musicVolume / 100.0f);

				Audio->getSound("dong")->Play();
			}
			else if (more_musicVolumeButton->HasBeenClicked())
			{
				musicVolume = musicVolume + 10 <= 100 ? musicVolume + 10 : musicVolume;

				std::stringstream ss;
				ss << musicVolume;
				currentMusicVolumeLabel->SetText(ss.str());

				Audio->setMusicVolume(musicVolume / 100.0f);

				Audio->getSound("ding")->Play();
			}
			//SFX
			if (less_soundFXVolumeButton->HasBeenClicked())
			{
				soundFXVolume = soundFXVolume - 10 >= 0 ? soundFXVolume - 10 : soundFXVolume;

				std::stringstream ss;
				ss << soundFXVolume;
				curentSFXVolumeLabel->SetText(ss.str());

				Audio->setSoundVolume(soundFXVolume / 100.0f);

				Audio->getSound("dong")->Play();
			}
			else if (more_soundFXVolumeButton->HasBeenClicked())
			{
				soundFXVolume = soundFXVolume + 10 <= 100 ? soundFXVolume + 10 : soundFXVolume;

				std::stringstream ss;
				ss << soundFXVolume;
				curentSFXVolumeLabel->SetText(ss.str());

				Audio->setSoundVolume(soundFXVolume / 100.0f);

				Audio->getSound("ding")->Play();
			}

			//APPLY / CANCEL
			if (applyButton->HasBeenClicked())
			{
				//APPLY OPTIONS
				if (!isFullscreen)
				{
					switch (currentResolution)
					{
					case Resolution::_0800x0600:
						GameProperties::getInstance()->getVideoProperties()->screenWidth = 800;
						GameProperties::getInstance()->getVideoProperties()->screenHeight = 600;					
						break;
					case Resolution::_1024x0768:
						GameProperties::getInstance()->getVideoProperties()->screenWidth = 1024;
						GameProperties::getInstance()->getVideoProperties()->screenHeight = 768;
						break;
					case Resolution::_1280x0720:
						GameProperties::getInstance()->getVideoProperties()->screenWidth = 1280;
						GameProperties::getInstance()->getVideoProperties()->screenHeight = 720;
						break;
					case Resolution::_1440x0900:
						GameProperties::getInstance()->getVideoProperties()->screenWidth = 1440;
						GameProperties::getInstance()->getVideoProperties()->screenHeight = 900;
						break;
					case Resolution::_1600x0900:
						GameProperties::getInstance()->getVideoProperties()->screenWidth = 1600;
						GameProperties::getInstance()->getVideoProperties()->screenHeight = 900;
						break;
					case Resolution::_1920x1080:
						GameProperties::getInstance()->getVideoProperties()->screenWidth = 1920;
						GameProperties::getInstance()->getVideoProperties()->screenHeight = 1080;
						break;
					}				
					GAME->SetResolution(GameProperties::getInstance()->getVideoProperties()->screenWidth, GameProperties::getInstance()->getVideoProperties()->screenHeight);
				}

				if (GameProperties::getInstance()->getVideoProperties()->isFullscreen != isFullscreen)
				{
					GameProperties::getInstance()->getVideoProperties()->isFullscreen = isFullscreen;
					GAME->SetFullscreen(isFullscreen);
				}

				GameProperties::getInstance()->getAudioProperties()->masterVolume = mainSoundVolume / 100.0f;
				GameProperties::getInstance()->getAudioProperties()->musicVolume = musicVolume / 100.0f;
				GameProperties::getInstance()->getAudioProperties()->soundVolume = soundFXVolume / 100.0f;

				Audio->setMusicVolume(musicVolume / 100.0f);
				Audio->setSoundVolume(soundFXVolume / 100.0f);
				Audio->setMainVolume(mainSoundVolume / 100.0f);

				GameProperties::getInstance()->ApplyChanges();

				landingScreen->ResetGUI();

				Audio->getSound("ding")->Play();
								
				select_state = Select_Default;
				HideOptions();
			}
			else if (cancelButton->HasBeenClicked())
			{
				Audio->setMainVolume(GameProperties::getInstance()->getAudioProperties()->masterVolume);
				Audio->setMusicVolume(GameProperties::getInstance()->getAudioProperties()->musicVolume);
				Audio->setSoundVolume(GameProperties::getInstance()->getAudioProperties()->soundVolume);

				Audio->getSound("dong")->Play();
				select_state = Select_Default;
				HideOptions();
			}
			break;
		}

	}
}

void Landing_GUI::SetResolutionLabel()
{
	switch (currentResolution)
	{
	case Resolution::_0800x0600:
		currentResolutionLabel->SetText("800x600");
		break;
	case Resolution::_1024x0768:
		currentResolutionLabel->SetText("1024x768");
		break;
	case Resolution::_1280x0720:
		currentResolutionLabel->SetText("1280x720");
		break;
	case Resolution::_1440x0900:
		currentResolutionLabel->SetText("1440x900");
		break;
	case Resolution::_1600x0900:
		currentResolutionLabel->SetText("1600x0900");
		break;
	case Resolution::_1920x1080:
		currentResolutionLabel->SetText("1920x1080");
		break;
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

Menu_Select_State Landing_GUI::GetSelectState()
{
	return select_state;
}

void Landing_GUI::SetSelectState(Menu_Select_State state_)
{
	select_state = state_;
}

Level_Descriptor::Level_Descriptor(Level * level_) : hasDescriptorBeenSet(false)
{
	FontManager::getInstance()->GenerateFont("DESCRIPTOR_FONT", 22, "Font/Aaargh.ttf");
	FontManager::getInstance()->GenerateFont("DESCRIPTOR_FONT2", 18, "Font/Aaargh.ttf");
	FontManager::getInstance()->GenerateFont("DESCRIPTOR_FONT3", 32, "Font/Aaargh.ttf");

	
	mainImage = new GuiImage(level_, "LANDING_GUI_DESCRIPTOR", Vec2(0, 0));
	mainImage->Scale(Vec3(1.f, 3.f, 1));

	playButton = new SelectButton(level_, Vec2(0, -80), "Play", FontManager::getInstance()->GetFont("DESCRIPTOR_FONT3"), BOTTOM_LEFT);
	playButton->Scale(Vec3(0.5, 0.5, 1));
	playButton->isSelected = true;
	mainImage->addChild(playButton);

	levelName = new Label(level_, "Name: ", FontManager::getInstance()->GetFont("DESCRIPTOR_FONT"), Vec2(-40, 100), BOTTOM_LEFT, Colour::White());
	mainImage->addChild(levelName);

	levelPar = new Label(level_, "Par: ", FontManager::getInstance()->GetFont("DESCRIPTOR_FONT"), Vec2(-100, 80), BOTTOM_LEFT, Colour::White());
	mainImage->addChild(levelPar);

	reasonWhy = new MultiLineLabel(level_, "I like to write a number of things. None of which are really all that important.", 
		250, FontManager::getInstance()->GetFont("DESCRIPTOR_FONT2"), Vec2(0, -10), BOTTOM_LEFT, Colour::White());

	mainImage->addChild(reasonWhy);

	mainImage->Translate(Vec3(1110, 165, 0));

	Hide();
}


void Level_Descriptor::Hide()
{
	mainImage->Hide();
	playButton->Hide();
	levelName->Hide();
	levelPar->Hide();
	reasonWhy->Hide();
}

void Level_Descriptor::Show()
{
	mainImage->Show();
	playButton->Show();
	levelName->Show();
	levelPar->Show();
	reasonWhy->Show();
}

bool Level_Descriptor::GetVisible()
{
	return mainImage->IsVisible();
}

void Level_Descriptor::SetDescriptor(const Node * node_)
{
	Hide();

	/*if (mainImage->position.x != 0)
		mainImage->Translate(mainImage->position * -1);*/

	levelName->SetText("Name: " + node_->objectiveName);
	levelPar->SetText("Par: " + std::to_string(node_->par));
	reasonWhy->SetText(node_->description);

	Vec2 screenPos = node_->getScreenPosition();

	////mainImage->Translate(Vec3(mainImage->position.x - (node_->position.x + 10) + 650, mainImage->position.y - node_->position.y + 220, 0));
	//mainImage->Translate(Vec3(screenPos.x + (GameProperties::getVideoProperties()->screenWidth * 0.25f), screenPos.y, 0));
	Show();

	hasDescriptorBeenSet = true;
}

bool Level_Descriptor::DescriptorHasBeenSet()
{
	return hasDescriptorBeenSet;
}