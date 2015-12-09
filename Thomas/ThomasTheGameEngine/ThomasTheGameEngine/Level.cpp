#include "Level.h"
#include "OpenGLUtilities.h"
#include "ModelManager.h"
#include "LightManager.h"
#include "GuiElement.h"

Level::Level()
{
	mainCamera = new Camera(this);
	currentCamera = mainCamera;

	ambientLightColor = Colour(0.5f, 0.5f, 0.5f, 1);
	gameObjects.push_back(currentCamera);
}

Level::~Level()
{
	for (auto it = gameObjects.begin(); it != gameObjects.end(); it++)
	{
		gameObjects.erase(it);

		delete it._Ptr;
	}
	gameObjects.clear();
	gameObjectsToBeDeleted.clear();

	for (auto it = guiElements.begin(); it != guiElements.end(); it++)
	{
		guiElements.erase(it);

		delete it._Ptr;
	}
	guiElements.clear();
}

void Level::LevelRender()
{
	float ambient[] = { ambientLightColor.r, ambientLightColor.g, ambientLightColor.b, ambientLightColor.a };
	glUniform4fv(ModelManager::getInstance()->ambientLocation, 1, ambient);

	//Pre-Render
	for (int i = 0; i < gameObjects.size(); i++)
	{
		if (!gameObjects[i]->isFlagged)
			gameObjects[i]->PreRender();
	}
	LightManager::getInstance()->PushLights();


	//Render
	for (int i = 0; i < gameObjects.size(); i++)
	{
		if (!currentCamera->frustrum.checkObjectInside(gameObjects[i], currentCamera) && i != 0)
		{
			//printf("YOU SUCKS: %d \n", i);
		}

		if (!gameObjects[i]->isFlagged)
			gameObjects[i]->Render();
		else
			gameObjectsToBeDeleted.push_back(gameObjects[i]);
	}

	//UI
	for (int i = 0; i < guiElements.size(); i++)
	{
		if (guiElements[i]->IsVisible())
			guiElements[i]->Draw();
	}

	DebugRender();
	LevelCleanUp();
}

void Level::LevelUpdate(float _timeStep)
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		if (!gameObjects[i]->isFlagged)
			gameObjects[i]->Update(_timeStep);
	}

	for (int i = 0; i < guiElements.size(); i++)
	{
		guiElements[i]->Update(_timeStep);
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
	gameObjects.shrink_to_fit();
}

void Level::SetCamera(Camera * _c)
{
	currentCamera = _c;
}