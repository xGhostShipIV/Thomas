//Author:	Mathieu Violette
//Date:		2/17/2016

#pragma once

#include <Label.h>
#include <GuiImage.h>
#include <TextButton.h>

class Landing_GUI
{
private:
	bool isInstructionsShown, isInputIsClear;
public:
	Landing_GUI(Level *level_);
	~Landing_GUI();

	Button *PlayButton, *ExitButton;
	TextButton *InstructionsButton;
	GuiImage *InstructionsImage;

	void Update(float timeStep_);
};