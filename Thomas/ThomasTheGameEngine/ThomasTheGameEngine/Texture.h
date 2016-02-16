//Author:	Mathieu Violette, Nathan Senter
//Date:		11/06/2015, 11/24/2015

#pragma once
#include <SDL.h>
#include <string>
typedef unsigned int UINT32;

class Texture
{
public:
	enum TextureDataType
	{
		Float, UnsignedByte
	};

	Texture(SDL_Surface* _surface);
	Texture(void* _pixelData, UINT32 _width, UINT32 _height);
	~Texture();

	//Index in texture array
	UINT32 address;

	SDL_Surface* surface;

	//texture dimensions in pixels
	UINT32 width, height;

	//color of each pixel in the texture
	void* pixelData;

	TextureDataType dataType;
};