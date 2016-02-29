//Author:	Mathieu Violette
//Date:		2/29/2016

#pragma once

#include <TextButton.h>

class LevelSelectButton : public TextButton
{
public:
	LevelSelectButton(Level* level_, Vec2 screenPosition_, std::string labelText_, ScreenAnchor anchor_ = ScreenAnchor::CENTER, Colour unpressedTextColour_ = Colour::Yellow(), Colour pressedTextColour_ = Colour::Lime());
	~LevelSelectButton();

	bool isSelected;

	virtual void SelectSprite() override;
};