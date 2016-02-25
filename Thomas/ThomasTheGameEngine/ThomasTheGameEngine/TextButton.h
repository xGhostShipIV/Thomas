//Author:	Mathieu Violette
//Date:		2/25/2015

#ifndef _TEXT_BUTTON_H_
#define _TEXT_BUTTON_H_

#include "Button.h"
#include "Label.h"

class TextButton : public Button
{
protected:
	Label label;
	Colour unpressedTextColour, pressedTextColour;
public:
	TextButton(Level* level_, Vec2 screenPosition_, std::string labelText_, TTF_Font* font_, std::string textureUnpressed_, std::string textureHover_, ScreenAnchor anchor_ = ScreenAnchor::BOTTOM_LEFT, Colour unpressedTextColour_ = Colour::Black(), Colour pressedTextColour_ = Colour::Lime());
	~TextButton();

	virtual void SelectSprite() override;
};

#endif