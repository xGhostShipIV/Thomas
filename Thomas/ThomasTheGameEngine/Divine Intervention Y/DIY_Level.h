#pragma once
#include <Level.h>
#include "Layer.h"
#include <Rigidbody.h>
#include "Pointer.h"
#include "DIY_Level_GUI.h"

enum DIY_Level_State
{
	PLAYING, PAUSED, VICTORY
};

enum DIY_Level_Playing_State
{
	SHOOTING, WATCHING
};

enum DIY_Level_Victory_State
{
	REVIEW, LEVEL_SELECT
};

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
	////bool isPaused;

	DIY_Level_State levelState;
	DIY_Level_Playing_State playingState;
	DIY_Level_Victory_State victoryState;

	std::vector<Layer *> layers;

	int HasObjectives();

	GameObject * layerContainer;
	DIY_Level_GUI * gui;

	bool rotateLevel;

	void LevelUpdate(float timeStep_) override;

	void SetLayerPlane(Layer *);

	void AdjustObjectiveCount(int);
private:
	GameObject * skybox, *playerBall;
	Rigidbody * planeRigidBody;

	std::string fileName;

	int objectiveCount;

	bool isShooting;
	bool isPausedKeyStillPressed;

	void PauseLogic();
};

