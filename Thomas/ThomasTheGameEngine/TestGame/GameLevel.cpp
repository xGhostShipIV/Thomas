#include "GameLevel.h"
#include <dependencies\TinyXML\tinyxml2.h>

#include <ModelManager.h>
#include <RenderableComponent.h>

#include "FPS_Inputs.h"

GameLevel::GameLevel(std::string fileName_)
{
	ModelManager::getInstance()->CreateSkybox("skybox", 1000.0f);
	ModelManager::getInstance()->loadTexture("skybox1", "Images/spaceSkybox.tif");
	ModelManager::getInstance()->loadTexture("layerGrid", "Images/grid.png");

	tinyxml2::XMLDocument doc;

	//Tries to load the file, quits if it fails
	if (doc.LoadFile(fileName_.c_str()) != tinyxml2::XML_NO_ERROR) return;

	//Grabs first element
	tinyxml2::XMLElement * element = doc.RootElement();

	//set par
	par = element->IntAttribute("par");
	strokeCount = 0;

	int numLayers = 0;
	//grab size element and reserve memory for the layers
	//Possibly determine scale of them?
	if (element->Attribute("size") == "SMALL"){
		numLayers = 3;
	}
	else if (element->Attribute("size", "MEDIUM")){
		numLayers = 4;
	}
	else{
		numLayers = 5;
	}

	//set up skybox
	skybox = new GameObject(this, currentCamera->position);

	RenderableComponent * r = new RenderableComponent("skybox", std::string(element->Attribute("skybox")), skybox);
	r->SetEffecctedByLight(false, false, false);


	element = element->FirstChildElement("Layer");
	tinyxml2::XMLElement * objectElement = element->FirstChildElement("Object");

	for (int i = 0; i < numLayers; i++)
	{
		//Temporary storage for the gameobject to be passed to the layer
		std::vector<GameObject *> gameObjects;

		if (objectElement)
			do
			{
				GameObject * object;

				if (objectElement->Attribute("type", "PlanetHorizontal")){

				}
				else if (objectElement->Attribute("type", "PlanetVertical")){

				}
				else if (objectElement->Attribute("type", "Asteroids")){

				}
				else if (objectElement->Attribute("type", "Wormhole")){

				}
				else{

				}

				gameObjects.push_back(object);

				//point to next object element
				objectElement = objectElement->NextSiblingElement("Object");


			} while (objectElement);

		//create layer in the list
		layers.push_back(new Layer(this, Vec3(0, -2 + i * 1.5, 0), gameObjects));

		//Sets element pointer to the next layer

		element = element->NextSiblingElement("Layer");

		if (!element)break;

		objectElement = element->FirstChildElement("Object");
	}


	ModelManager::getInstance()->PushModels();

	new FPS_TURN_LEFT(currentCamera, MouseMovement::Negative_X);
	new FPS_TURN_RIGHT(currentCamera, MouseMovement::Positive_X);
	new FPS_TURN_UP(currentCamera, MouseMovement::Positive_Y);
	new FPS_TURN_DOWN(currentCamera, MouseMovement::Negative_Y);

	SDL_SetRelativeMouseMode(SDL_TRUE);
}


GameLevel::~GameLevel()
{
}

bool GameLevel::HasObjectives()
{
	return true;
}
