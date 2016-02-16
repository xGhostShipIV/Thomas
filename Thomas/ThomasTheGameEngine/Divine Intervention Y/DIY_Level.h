#pragma once
#include <Level.h>
#include "Layer.h"
#include <Rigidbody.h>
#include "Pointer.h"
#include "DIY_Level_GUI.h"

class DIY_Level :
	public Level
{
public:
	DIY_Level(std::string fileName_);
	~DIY_Level();

	void LoadContent() override;

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
	GameObject * skybox, *playerBall;
	PlaneCollider * layerPlane;
	DIY_Level_GUI * gui;

	std::string fileName;

	bool isShooting;
};

