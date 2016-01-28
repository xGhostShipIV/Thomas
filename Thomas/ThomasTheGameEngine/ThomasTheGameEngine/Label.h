//Author:	Mathieu Violette
//Date:		12/01/2015

#ifndef LABEL_H
#define LABEL_H

#include "GuiElement.h"
#include "FontManager.h"
#include "Colour.h"
#include <string>
#include "TextSprite.h"

class Level;

class Label : public GuiElement
{
protected:
	TextSprite* txtSprite;
	std::string text;
	TTF_Font* font;
	Colour textColour;
public:
	
	Label(Level* _level, std::string _text, TTF_Font* _font, Vec2 _screenPosition, ScreenAnchor anchor_ = ScreenAnchor::BOTTOM_LEFT, Colour _textColour = Colour::Black());
	~Label();
	virtual void Update(float _deltaTime) override;
	//virtual void Draw() override;

	virtual void OnClick();
	virtual void OnHover();

	void SetTextColor(Colour _colour);

	void SetText(std::string _text);
	std::string GetText() const;
};

#endif