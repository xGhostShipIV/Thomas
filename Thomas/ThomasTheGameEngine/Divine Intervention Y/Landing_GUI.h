//Author:	Mathieu Violette
//Date:		2/17/2016

#pragma once

#include <Label.h>
#include <GuiImage.h>
#include <Button.h>

class Landing_GUI
{
private:
public:
	Landing_GUI(Level *level_);
	~Landing_GUI();

	Button *PlayButton, *ExitButton;

	void Update(float timeStep_);
};