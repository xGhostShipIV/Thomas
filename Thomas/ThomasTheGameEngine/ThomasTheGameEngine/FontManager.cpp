#include "FontManager.h"

FontManager* FontManager::instance;

FontManager::FontManager(){}

FontManager* FontManager::getInstance()
{
	if (!instance)
		instance = new FontManager();

	return instance;
}

FontManager::~FontManager()
{
	for (auto it = fonts.begin(); it != fonts.end(); it++)
	{
		TTF_CloseFont(it->second);
	}
}

void FontManager::GenerateFont(std::string _fontID, int _fontSize, std::string _path)
{
	fonts.insert(std::pair<std::string, TTF_Font*>(_fontID, TTF_OpenFont(_path.c_str(), _fontSize)));
}

TTF_Font* FontManager::GetFont(std::string _fontID)
{
	return fonts.find(_fontID)->second;
}