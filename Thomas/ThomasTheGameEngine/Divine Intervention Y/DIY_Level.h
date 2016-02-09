#pragma once
#include <Level.h>
#include "Layer.h"
#include <Rigidbody.h>

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

	GameObject * layerContainer;

	bool rotateLevel;

	void LevelUpdate(float timeStep_) override;

	void SetLayerPlane(Layer *);
private:
	GameObject * skybox;
	PlaneCollider * layerPlane;
};

