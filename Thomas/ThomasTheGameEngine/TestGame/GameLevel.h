#pragma once
#include <Level.h>
#include "Layer.h"

class GameLevel :
	public Level
{
public:
	GameLevel(std::string fileName_);
	~GameLevel();

	int par;
	int strokeCount;
	int levelBounds;

	std::vector<Layer *> layers;

	bool HasObjectives();

	GameObject * layerContainer;

	bool rotateLevel;
private:
	GameObject * skybox;
};

