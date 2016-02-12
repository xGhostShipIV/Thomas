//Author:	Mathieu Violette
//Date:		2/11/2016

#pragma once

#include <Label.h>
#include <GuiImage.h>

class DIY_Level_GUI
{
private:
	int par, objectives, strokes;
public:
	DIY_Level_GUI(Level *level_, int par_, int objectives_);
	~DIY_Level_GUI();

	float shotPower;

	Label *ParLabel, *StrokeLabel, *ObjectivesLabel;
	Label *ParCountLabel, *StrokeCountLabel, *ObjectivesCountLabel;
	GuiImage *ShotPowerMeterFrame, *ShotPowerMeter, *ParBackground, *StrokeBackground, *ObjectivesBackground;

	void Update(float timeStep_);

	//Used to update the number of remaining objectives
	void SetObjectivesRemaining(int objectives_);

	//Used to update the stroke count
	void PlayerTookAStroke(int strokeIncrement = 1);
};