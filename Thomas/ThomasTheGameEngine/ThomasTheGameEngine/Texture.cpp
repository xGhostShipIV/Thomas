#include "Texture.h"

Texture::Texture(float *_pixelData, UINT32 _width, UINT32 _height) : pixelData(_pixelData), width(_width), height(_height)
{
}

Texture::Texture(std::string _fileName)
{

}

Texture::~Texture()
{
	delete pixelData;
}

