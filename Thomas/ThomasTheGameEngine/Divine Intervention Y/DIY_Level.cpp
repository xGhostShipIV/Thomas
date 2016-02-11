#include "DIY_Level.h"
#include <dependencies\TinyXML\tinyxml2.h>

#include <ModelManager.h>
#include <RenderableComponent.h>
#include <InputHandler.h>
#include <Game.h>


#include "GameCamera.h"
#include "PlanetHorizontal.h"
#include "PlanetVertical.h"
#include "AsteroidField.h"
#include "Wormhole.h"
#include "WarpGate.h"
#include "PlayerBall.h"

DIY_Level::DIY_Level(std::string fileName_)
{
	currentCamera = new GameCamera(this, Vec3(0, 0.75f, -7), Vec3(0, 0, 0));

	Models->CreateSkybox("skybox", 1000.0f);
	Models->loadTexture("skybox1", "Images/spaceSkybox.tif");
	Models->loadTexture("layerGrid", "Images/grid.png");
	Models->loadTexture("planet1", "Images/aruba.tif");
	Models->loadTexture("meteorTex1", "Images/meteor_texture.tif");
	Models->loadTexture("meteorTex2", "Images/meteor_texture_2.tif");
	Models->loadTexture("meteorTex3", "Images/meteor_texture_3.tif");
	Models->loadTexture("gateTexture", "Images/rosary.png");
	Models->loadTexture("ballSkin", "Images/8ball.png");

	float f[] =
	{
		1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f
	};

	Models->createTexture("white", f, 2, 2);

	Models->loadModel("sphere", "Models/planet.obj", true);
	Models->loadModel("meteor1", "Models/meteor_01.obj", true);
	Models->loadModel("meteor2", "Models/meteor_02.obj", true);
	Models->loadModel("meteor3", "Models/meteor_03.obj", true);
	Models->loadModel("warpGate", "Models/space_station.obj", true);
	Models->loadModel("pointer", "Models/pointer.obj", true);

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

	//layerPlane = PlaneCollider();

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

	bool setPlayerLayer = false;

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
				setPlayerLayer = true;

				object = new PlayerBall(this, Vec3(x, -2 + i * 1.5f, z));
			}
			else{

			}

			gameObjects.push_back(object);

			//point to next object element
			objectElement = objectElement->NextSiblingElement("Object");


		} while (objectElement);

		//create layer in the list
		layers.push_back(new Layer(this, Vec3(0, -2 + i * 1.5, 0), gameObjects));

		//Attaches the plane collider to last layer added if it contains the players start point
		if (setPlayerLayer)
		{
			layerPlane = new PlaneCollider(*(layers.end() - 1), Vec3(0, 1, 0));
			layers.back()->getComponent<Rigidbody>()->col = layerPlane;
			setPlayerLayer = false;
		}

		//Sets element pointer to the next layer

		element = element->NextSiblingElement("Layer");

		if (!element)break;

		objectElement = element->FirstChildElement("Object");
	}

	for (int i = 0; i < layers.size(); i++)
		layerContainer->addChild(layers[i]);


	ModelManager::getInstance()->PushModels();
}


DIY_Level::~DIY_Level()
{
}

bool DIY_Level::HasObjectives()
{
	return true;
}

void DIY_Level::LevelUpdate(float timeStep_)
{
	Level::LevelUpdate(timeStep_);

	if (Input->isMouseDown(SDL_BUTTON_RIGHT))
	{
		layerContainer->Rotate(Quat(Input->deltaMouse().x * timeStep_, Vec3(0, 1.0f, 0)));
	}

	if (Input->isKeyDown(SDLK_ESCAPE))
		GAME->setRunning(false);
}