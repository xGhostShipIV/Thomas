#include "GameLevel.h"
#include <dependencies\TinyXML\tinyxml2.h>

#include <ModelManager.h>
#include <RenderableComponent.h>

#include "FPS_Inputs.h"
#include "CameraControls.h"

#include "GameCamera.h"
#include "PlanetHorizontal.h"
#include "PlanetVertical.h"
#include "AsteroidField.h"
#include "Wormhole.h"
#include "WarpGate.h"

GameLevel::GameLevel(std::string fileName_)
{
	currentCamera = new GameCamera(this, Vec3(0, 0.75f, -7), Vec3(0, 0, 0));

	ModelManager::getInstance()->CreateSkybox("skybox", 1000.0f);
	ModelManager::getInstance()->loadTexture("skybox1", "Images/spaceSkybox.tif");
	ModelManager::getInstance()->loadTexture("layerGrid", "Images/grid.png");
	ModelManager::getInstance()->loadTexture("planet1", "Images/aruba.tif");
	ModelManager::getInstance()->loadTexture("meteorTex1", "Images/meteor_texture.tif");
	ModelManager::getInstance()->loadTexture("meteorTex2", "Images/meteor_texture_2.tif");
	ModelManager::getInstance()->loadTexture("meteorTex3", "Images/meteor_texture_3.tif");
	ModelManager::getInstance()->loadTexture("gateTexture", "Images/rosary.png");

	ModelManager::getInstance()->loadModel("sphere", "Models/planet.obj", true);
	ModelManager::getInstance()->loadModel("meteor1", "Models/meteor_01.obj", true);
	ModelManager::getInstance()->loadModel("meteor2", "Models/meteor_02.obj", true);
	ModelManager::getInstance()->loadModel("meteor3", "Models/meteor_03.obj", true);
	ModelManager::getInstance()->loadModel("warpGate", "Models/space_station.obj", true);

	tinyxml2::XMLDocument doc;

	//Tries to load the file, quits if it fails
	if (doc.LoadFile(fileName_.c_str()) != tinyxml2::XML_NO_ERROR) return;

	//Grabs first element
	tinyxml2::XMLElement * element = doc.RootElement();

	//set par
	par = element->IntAttribute("par");
	strokeCount = 0;

	int numLayers = 0;

	rotateLevel = false;

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
	layerContainer = new GameObject(this, Vec3(0, 0, 0));

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

				float x = objectElement->FloatAttribute("x");
				float z = objectElement->FloatAttribute("z");

				if (objectElement->Attribute("type", "PlanetHorizontal")){

					std::string textureName = objectElement->Attribute("texture");

					object = new PlanetHorizontal(this, Vec3(x, -2 + i * 1.5, z), textureName);
				}
				else if (objectElement->Attribute("type", "PlanetVertical")){
					std::string textureName = objectElement->Attribute("texture");

					object = new PlanetVertical(this, Vec3(x, -2 + i * 1.5, z), textureName);
				}
				else if (objectElement->Attribute("type", "Asteroids")){
					object = new AsteroidField(this, Vec3(x, -2 + i * 1.5, z), 1, 6);
				}
				else if (objectElement->Attribute("type", "Wormhole")){
					object = new Wormhole(this, Vec3(x, -2 + i * 1.5, z), i);
				}
				else if (objectElement->Attribute("type", "WarpGate")){
					object = new WarpGate(this, Vec3(x, -2 + i * 1.5, z), Quat(1, 0, 0, 0));
				}
				else if (objectElement->Attribute("type", "Player1Start")){

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

	for (int i = 0; i < layers.size(); i++) 
		layerContainer->addChild(layers[i]);

	ModelManager::getInstance()->PushModels();

	//new FPS_TURN_LEFT(currentCamera, MouseMovement::Negative_X);
	//new FPS_TURN_RIGHT(currentCamera, MouseMovement::Positive_X);
	//new FPS_TURN_UP(currentCamera, MouseMovement::Positive_Y);
	//new FPS_TURN_DOWN(currentCamera, MouseMovement::Negative_Y);
	//new Camera_Forward(currentCamera, SDLK_w);
	//new Camera_Right(currentCamera, SDLK_d);
	//new Camera_Back(currentCamera, SDLK_s);

	SDL_SetRelativeMouseMode(SDL_TRUE);
}


GameLevel::~GameLevel()
{
}

bool GameLevel::HasObjectives()
{
	return true;
}
