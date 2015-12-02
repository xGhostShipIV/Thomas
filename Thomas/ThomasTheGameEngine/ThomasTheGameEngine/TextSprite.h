//Author:	Mathieu Violette
//Date:		12/01/2015

#pragma once
#include <string>
#include <SDL_ttf.h>
#include "Texture.h"
#include "Colour.h"

class TextSprite : public Texture
{
public:
	TextSprite(std::string _text, TTF_Font* _font, Colour _textColor);
	~TextSprite();

	void ReCreateTexture(std::string _text, TTF_Font* _font, Colour _textColor);

	//Location in Texture Map
	UINT32 mapAddress;
};