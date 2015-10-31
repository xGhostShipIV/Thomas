#pragma once
#include "Camera.h"
#include <vector>

class Level
{
public:
	Level();
	~Level();

	GLuint cameraLocation;

	Camera * mainCamera;
	Camera * currentCamera;

	//Lists that call all updates/renders for gameObjects in the game
	//As well as a list that will collect all flagged gameObjects and delete them
	std::vector<GameObject *> gameObjects;
	std::vector<GameObject *> gameObjectsToBeDeleted;

	void LevelRender();
	virtual void LevelUpdate(UINT32 _timeStep);

	void SetCamera(Camera * _c);

	void LevelCleanUp();

protected:
	virtual void DebugRender(){};
};

