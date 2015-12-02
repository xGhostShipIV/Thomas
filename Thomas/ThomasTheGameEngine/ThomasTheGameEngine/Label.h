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
	UINT32 texture;
	std::string text;
	TTF_Font* font;
	Colour textColour;
public:
	
	Label(Level* _level, std::string _text, Vec2 _screenPosition, TTF_Font* _font, Colour _textColour = Colour::Black());
	~Label();
	virtual void Update(float _deltaTime) override;
	//virtual void Draw() override;

	virtual void OnClick();
	virtual void OnHover();

	virtual bool CheckMouseCollision(int _x, int _y);

	void SetTextColor(Colour _colour);

	void SetText(std::string _text);
	std::string GetText() const;
};

#endif