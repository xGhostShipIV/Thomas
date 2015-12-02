#include "Texture.h"
#include <iostream>

Texture::Texture(SDL_Surface* _surface)
	: width(_surface->w), height(_surface->h), surface(_surface)
{
	dataType = TextureDataType::UnsignedByte;

	SDL_PixelFormat *fmt;	
	fmt = _surface->format;

	if ((int)fmt->BitsPerPixel == 8)
	{
		SDL_Surface* _formattedSurf = SDL_ConvertSurfaceFormat(_surface, SDL_PIXELFORMAT_RGBA8888, 0);
		SDL_Surface* temp = _surface;
		_surface = _formattedSurf;
		
		SDL_FreeSurface(temp);
	}

	pixelData = _surface->pixels;
	
	//fmt = _surface->format; 	std::cout << (int)fmt->BitsPerPixel << "\n";

	//////Flip Pixels Around Vertically... for some reason our textures are flipped
	////unsigned char *pixelz = new unsigned char[width * height * 4];

	////for (int i = 0; i < width * height; i++)
	////{
	////	pixelz[((width * height) - i) * 4 + 0] = ((unsigned char*)_surface->pixels)[i * 4 + 0];
	////	pixelz[((width * height) - i) * 4 + 1] = ((unsigned char*)_surface->pixels)[i * 4 + 1];
	////	pixelz[((width * height) - i) * 4 + 2] = ((unsigned char*)_surface->pixels)[i * 4 + 2];
	////	pixelz[((width * height) - i) * 4 + 3] = ((unsigned char*)_surface->pixels)[i * 4 + 3];
	////}

	////pixelData = pixelz;


	//Uint32 temp, pixel;
	//Uint8 red, green, blue, alpha;

	////Get Pixel Data
	//pixelData = new float[width * height * 4];

	
	//SDL_LockSurface(_surface);
	//

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

Texture::~Texture()
{
	if (surface)
		SDL_FreeSurface(surface);
	else
		delete pixelData;
}

