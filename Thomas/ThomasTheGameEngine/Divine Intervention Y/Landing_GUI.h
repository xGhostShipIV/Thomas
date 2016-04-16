//Author:	Mathieu Violette, Nathan Senter
//Date:		2/17/2016, 2/26/2016 (NS), 4/5/2016(NS)

#pragma once

#include <dependencies\TinyXML\tinyxml2.h>
#include <Label.h>
#include <GuiImage.h>
#include <TextButton.h>
#include "LevelSelectButton.h" //SelectButton

class Level;
class Node;
class LandingScreen;

enum Menu_State{
	Title,
	Tranisiton,
	Select
};

enum Menu_Select_State
{
	Select_Default, Select_Instructions, Select_Options
};

enum Resolution
{
	_1920x1080, _1600x0900, _1440x0900, _1280x0720, _1024x0768, _0800x0600
};

class Level_Descriptor
{
	friend class Landing_GUI;
private:
	GuiImage * mainImage;

	SelectButton * playButton;

	Label * levelName;
	Label * levelPar;
	MultiLineLabel * reasonWhy;

	bool hasDescriptorBeenSet;
public:
	Level_Descriptor(Level *);
	~Level_Descriptor(){}

	void Hide();
	void Show();
	bool GetVisible();

	void SetDescriptor(const Node *);
	bool DescriptorHasBeenSet();
};

class Landing_GUI
{
private:
	Menu_State state;
	Menu_Select_State select_state;

	Level *level;

	void SetResolutionLabel();
public:
	Landing_GUI(Level *level_);
	~Landing_GUI();

	//SelectButton *PlayButton;
	TextButton *ExitButton, *OptionsButton;
	TextButton *InstructionsButton;
	GuiImage *InstructionsImage;

	GuiImage * gameTitle;
	Label * pressStart;
	//MultiLineLabel * detailsLabel;

	/* OPTIONS */
	Label *optionsTitle, *fullscreenOption, *resolutionOption, *musicVolumeOption, *soundFXVolumeOption, *mainSoundVolumeOption;
	TextButton *fullscreenButton, *cancelButton, *applyButton;
	Button *less_resolutionButton, *more_resolutionButton, *less_musicVolumeButton, *more_musicVolumeButton, *less_soundFXVolumeButton, *more_soundFXVolumeButton,
		*less_mainSoundVolumeButton, *more_mainSoundVolumeButton;
	Label *currentResolutionLabel, *currentMusicVolumeLabel, *curentSFXVolumeLabel, *currentMainSoundVolumeLabel;
	bool isFullscreen;
	int musicVolume, soundFXVolume, mainSoundVolume;
	Resolution currentResolution;

	bool titleIsShown;

	LandingScreen * landingScreen;

	Level_Descriptor * levelDescriptor;

	Menu_State GetState();
	void SetState(Menu_State);

	Menu_Select_State GetSelectState();
	void SetSelectState(Menu_Select_State state_);

	void Update(float timeStep_);
	void SetLevelName(std::string name_);
	
	void ShowSelectButtons();
	void HideSelectButtons();

	//Populates options with proper values.
	void GetOptions();
	void ShowOptions();
	void HideOptions();
};