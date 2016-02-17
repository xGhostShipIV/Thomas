#include "Level.h"
#include "OpenGLUtilities.h"
#include "ModelManager.h"
#include "LightManager.h"
#include "GuiElement.h"

#include "Button.h"
#include "GuiImage.h"
#include "Label.h"

Level::Level()
{
	mainCamera = new Camera(this);
	currentCamera = mainCamera;

	ambientLightColor = Colour(0.5f, 0.5f, 0.5f, 1);

	hasCalledInit = false;
}

Level::~Level()
{
	for (auto it = gameObjects.begin(); it != gameObjects.end(); it++)
	{
		delete *it;
	}
	gameObjects.clear();

	for (auto it = guiElements.begin(); it != guiElements.end(); it++)
	{
		switch ((*it)->type)
		{
		case GuiType::BUTTON:
			delete (Button*) *it;
			break;
		case GuiType::IMAGE:
			delete ((GuiImage*)*it);
			break;
		case GuiType::LABEL:
			delete ((Label*)*it);
			break;
		}		
	}
	guiElements.clear();
}

void Level::init()
{
	//Will only load models/textures of a level once
	if (!hasCalledInit)
	{
		LoadContent();
		hasCalledInit = true;

		Models->PushModels();
	}
}

void Level::LoadContent(){}

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
		//if (!currentCamera->frustrum.checkObjectInside(gameObjects[i], currentCamera) && i != 0)
		//{
		//	//printf("YOU SUCKS: %d \n", i);
		//}

		if (!gameObjects[i]->isFlagged)
			gameObjects[i]->Render();
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
	for (int i = gameObjects.size() - 1; i >= 0; i--)
	{
		if (gameObjects[i]->isFlagged)
		{
			auto it = (gameObjects.begin() + i);
			gameObjects.erase(it);
		}
	}

	gameObjects.shrink_to_fit();
}

GameObject * Level::FindGameObjectWithTag(Tag _tag)
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		if (gameObjects[i]->hasTag(_tag))return gameObjects[i];
	}
}

void Level::SetAmbientColor(Colour _c)
{
	ambientLightColor = _c;
}

void Level::SetCamera(Camera * _c)
{
	currentCamera = _c;
}