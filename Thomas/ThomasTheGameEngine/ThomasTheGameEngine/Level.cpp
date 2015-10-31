#include "Level.h"
#include "OpenGLUtilities.h"

Level::Level()
{
	mainCamera = new Camera();
	currentCamera = mainCamera;

	gameObjects.push_back(currentCamera);
}


Level::~Level()
{
	LevelCleanUp();
}

void Level::LevelRender()
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		if (!gameObjects[i]->isFlagged)
			gameObjects[i]->Render();
		else
			gameObjectsToBeDeleted.push_back(gameObjects[i]);
	}

	DebugRender();
}

void Level::LevelUpdate(UINT32 _timeStep)
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		if (!gameObjects[i]->isFlagged)
			gameObjects[i]->Update(_timeStep);
	}
}

void Level::LevelCleanUp()
{
	for (auto it = gameObjectsToBeDeleted.begin(); it != gameObjectsToBeDeleted.end(); it++)
	{
		gameObjects.erase(it);

		delete it._Ptr;
	}
	gameObjectsToBeDeleted.clear();
}

void Level::SetCamera(Camera * _c)
{
	currentCamera = _c;
}