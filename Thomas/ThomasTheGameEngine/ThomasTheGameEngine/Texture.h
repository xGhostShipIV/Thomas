//Author:	Mathieu Violette
//Date:		11/06/2015

#pragma once

#include <string>
typedef unsigned int UINT32;


class Texture
{
public:
	Texture(float* _pixelData, UINT32 _width, UINT32 _height);
	Texture(std::string _fileName);
	~Texture();

	//Index in texture array
	UINT32 address;

	//texture dimensions in pixels
	UINT32 width, height;

	//color of each pixel in the texture
	float* pixelData;
};