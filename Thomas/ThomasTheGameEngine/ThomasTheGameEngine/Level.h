#pragma once
#include "Camera.h"
#include <vector>

/*
	A level acts as a scene in the game. All game objects are specific to a level
	and the level will update, render and delete all its own gameObjects so the user
	need not worry about it.
*/
class Level
{
public:
	Level();
	~Level();

	GLuint cameraLocation;

	//A camera is a default gameObject in a level
	Camera * mainCamera;
	Camera * currentCamera;

	//Lists that call all updates/renders for gameObjects in the game
	//As well as a list that will collect all flagged gameObjects and delete them
	std::vector<GameObject *> gameObjects;
	std::vector<GameObject *> gameObjectsToBeDeleted;

	//Renders and updates all gameObjects in the game
	void LevelRender();
	virtual void LevelUpdate(UINT32 _timeStep);

	//Sets the current camera
	void SetCamera(Camera * _c);

	//Will delete all gameObjects that have been flagged for deletion
	void LevelCleanUp();

protected:
	virtual void DebugRender(){};
};

