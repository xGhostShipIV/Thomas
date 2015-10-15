#pragma once

#include "dependencies\TinyXML\tinyxml2.h"

class GameProperties
{
public:
	~GameProperties();

	//Returns pointer to singleton properties
	//Creates one if none exists
	static GameProperties * getInstance(){
		if (!instance) instance = new GameProperties();
		return instance;
	}

	//A struct containing all relavant video properties
	struct VideoProperties{
		float aspectRatio;
		float drawDistance;
		float screenWidth;
		float screenHeight;
		bool isFullscreen;

		//Reads video property values from the xml and assigns
		void readValues();

		//Writes changed values to xml
		void writeValues();
	};

	//Struct containing audio properties
	struct AudioProperties{
		float masterVolume;
		float musicVolume;
		float soundVolume;

		void readValues();
		void writeValues();
	};

	//Called when you click the apply after changing some settings
	//Writes current values to the xml and saves it
	static void ApplyChanges(){
		vp->writeValues();
		ap->writeValues();

		doc.SaveFile("properties.xml");
	}

	//Returns the address to the video propery struct
	static VideoProperties * getVideoProperties(){
		return vp;
	}

	//Returns the address to audio property struct
	static AudioProperties * getAudioProperties(){
		return ap;
	}

private:
	GameProperties();

	//Single pointer to GameProperties object
	static GameProperties * instance;

	//Single pointers to Property structs
	static VideoProperties * vp;
	static AudioProperties * ap;

	//A reference to the xml document
	static tinyxml2::XMLDocument doc;
};

