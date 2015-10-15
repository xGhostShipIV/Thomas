#include "GameProperties.h"
#include <iostream>
#include <string>

GameProperties::VideoProperties * GameProperties::vp;
GameProperties::AudioProperties * GameProperties::ap;
tinyxml2::XMLDocument GameProperties::doc;

//Initializes the video and audio property structs
//And reads the values from the xml assigning them
GameProperties::GameProperties()
{
	vp = new VideoProperties();
	ap = new AudioProperties();

	vp->readValues();
	ap->readValues();

	doc.LoadFile("properties.xml");
}


GameProperties::~GameProperties()
{
	delete vp;
	delete ap;
}

//Reads the values from the xml and assigns them to the audio properties
void GameProperties::AudioProperties::readValues()
{
	tinyxml2::XMLElement * element = doc.FirstChildElement("AudioProperty")->FirstChildElement("property");

	masterVolume = std::stoi(element->GetText());
	element = element->NextSiblingElement("property");
	musicVolume = std::stoi(element->GetText());
	element = element->NextSiblingElement("property");
	soundVolume = std::stoi(element->GetText());
}

//Writes current audio values to the xml
void GameProperties::AudioProperties::writeValues()
{
	tinyxml2::XMLElement * element = doc.FirstChildElement("AudioProperty")->FirstChildElement("property");

	element->SetText(masterVolume);
	element = element->NextSiblingElement("property");
	element->SetText(musicVolume);
	element = element->NextSiblingElement("property");
	element->SetText(soundVolume);
}

//Reads video properties from xml and assigns them
void GameProperties::VideoProperties::readValues()
{
	tinyxml2::XMLElement * element = doc.FirstChildElement("VideoProperty")->FirstChildElement("property");

	aspectRatio = std::stoi(element->GetText());
	element = element->NextSiblingElement("property");
	drawDistance = std::stoi(element->GetText());
	element = element->NextSiblingElement("property");
	screenWidth = std::stoi(element->GetText());
	element = element->NextSiblingElement("property");
	screenHeight = std::stoi(element->GetText());
	element = element->NextSiblingElement("property");
	isFullscreen = std::stoi(element->GetText());
}

//Writes current video values to xml
void GameProperties::VideoProperties::writeValues()
{
	tinyxml2::XMLElement * element = doc.FirstChildElement("VideoProperty")->FirstChildElement("property");

	element->SetText(aspectRatio);
	element = element->NextSiblingElement("property");
	element->SetText(drawDistance);
	element = element->NextSiblingElement("property");
	element->SetText(screenWidth);
	element = element->NextSiblingElement("property");
	element->SetText(screenHeight);
	element = element->NextSiblingElement("property");
	element->SetText(isFullscreen);
}
