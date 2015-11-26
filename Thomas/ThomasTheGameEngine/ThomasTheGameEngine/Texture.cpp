#include "Texture.h"
#include <iostream>

Texture::Texture(SDL_Surface* _surface)
	: width(_surface->w), height(_surface->h)
{
	dataType = TextureDataType::UnsignedByte;
	pixelData = _surface->pixels;

	////Get Pixel Data
	//pixelData = new float[width * height * 4];

	//SDL_PixelFormat *fmt;
	//Uint32 temp, pixel;
	//Uint8 red, green, blue, alpha;

	//fmt = _surface->format;
	//SDL_LockSurface(_surface);
	//
	//std::cout << (int)fmt->BitsPerPixel << "\n\n";

	//for (int i = 0; i < width * height; i++)
	//{

	//	pixel = ((Uint32*)_surface->pixels)[i];

	//	/* Get Red component */
	//	temp = pixel & fmt->Rmask;  /* Isolate red component */
	//	temp = temp >> fmt->Rshift; /* Shift it down to 8-bit */
	//	temp = temp << fmt->Rloss;  /* Expand to a full 8-bit number */
	//	red = (Uint8)temp;

	//	/* Get Green component */
	//	temp = pixel & fmt->Gmask;  /* Isolate green component */
	//	temp = temp >> fmt->Gshift; /* Shift it down to 8-bit */
	//	temp = temp << fmt->Gloss;  /* Expand to a full 8-bit number */
	//	green = (Uint8)temp;

	//	/* Get Blue component */
	//	temp = pixel & fmt->Bmask;  /* Isolate blue component */
	//	temp = temp >> fmt->Bshift; /* Shift it down to 8-bit */
	//	temp = temp << fmt->Bloss;  /* Expand to a full 8-bit number */
	//	blue = (Uint8)temp;

	//	/* Get Alpha component */
	//	temp = pixel & fmt->Amask;  /* Isolate alpha component */
	//	temp = temp >> fmt->Ashift; /* Shift it down to 8-bit */
	//	temp = temp << fmt->Aloss;  /* Expand to a full 8-bit number */
	//	alpha = (Uint8)temp;

	//	/*if ((int)alpha > 0)
	//		std::cout << "R: " << (int)red / 255.0f << " G: " << (int)green / 255.0f << " B: " << (int)blue / 255.0f << " A: " << (int)alpha / 255.0f << "\n";*/

	//	pixelData[i + 3 * 4] = (int)red /   255.0f;
	//	pixelData[i + 2 * 4] = (int)green / 255.0f;
	//	pixelData[i + 1 * 4] = (int)blue /  255.0f;
	//	pixelData[i + 0 * 4] = (int)alpha / 255.0f;
	//}

	//SDL_UnlockSurface(_surface);
}

Texture::Texture(float *_pixelData, UINT32 _width, UINT32 _height)
	: pixelData(_pixelData), width(_width), height(_height)
{
	dataType = TextureDataType::Float;
}

Texture::Texture(std::string _fileName)
{

}

Texture::~Texture()
{
	delete pixelData;
}

