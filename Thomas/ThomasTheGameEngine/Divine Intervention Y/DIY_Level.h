#pragma once
#include <Level.h>
#include "Layer.h"

class DIY_Level :
	public Level
{
public:
	DIY_Level(std::string fileName_);
	~DIY_Level();

	int par;
	int strokeCount;
	int levelBounds;

	std::vector<Layer *> layers;

	bool HasObjectives();

private:
	GameObject * skybox;
};

