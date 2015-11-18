#include "Level.h"
#include "OpenGLUtilities.h"
#include "ModelManager.h"
Level::Level()
{
	mainCamera = new Camera();
	currentCamera = mainCamera;

	ambientLightColor = Vec4(0.5f, 0.5f, 0.5f, 1.0f);
	gameObjects.push_back(currentCamera);
}

Level::~Level()
{
	LevelCleanUp();
}

void Level::LevelRender()
{
	float ambient[] = { ambientLightColor.x, ambientLightColor.y, ambientLightColor.z, ambientLightColor.w };
	glUniform4fv(ModelManager::getInstance()->ambientLocation, 1, ambient);

	//Pre-Render
	for (int i = 0; i < gameObjects.size(); i++)
	{
		if (!gameObjects[i]->isFlagged)
			gameObjects[i]->PreRender();
	}

	//Render
	for (int i = 0; i < gameObjects.size(); i++)
	{
		if (!currentCamera->frustrum.checkObjectInside(gameObjects[i], currentCamera) && i != 0)
		{
			printf("YOU SUCKS: %d \n", i);
		}

		if (!gameObjects[i]->isFlagged)
			gameObjects[i]->Render();
		else
			gameObjectsToBeDeleted.push_back(gameObjects[i]);
	}

	printf("\n");

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