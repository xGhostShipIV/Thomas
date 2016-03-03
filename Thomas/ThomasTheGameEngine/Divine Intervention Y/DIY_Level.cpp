#include "DIY_Level.h"
#include <dependencies\TinyXML\tinyxml2.h>

#include <ModelManager.h>
#include <AudioManager.h>
#include <RenderableComponent.h>
#include <InputHandler.h>
#include <Game.h>

#include "FocusCamera.h"
#include "GameCamera.h"
#include "PlanetHorizontal.h"
#include "PlanetVertical.h"
#include "AsteroidField.h"
#include "Wormhole.h"
#include "WarpGate.h"
#include "PlayerBall.h"
#include "ObjectivePlanet.h"
#include "Sun.h"

#include <PhysicsWorld.h>
#include "LandingScreen.h"

DIY_Level::DIY_Level(std::string fileName_) : fileName(fileName_), isPausedKeyStillPressed(false), hasFinishedLoading(false), PlayerHasShotBallIntoSun(false)
{
	levelState = DIY_Level_State::PLAYING;
	playingState = DIY_Level_Playing_State::SHOOTING;
	victoryState = DIY_Level_Victory_State::REVIEW;

	ambientLightColor = Colour(0.25f, 0.25f, 0.25f);
}

void DIY_Level::LoadContent()
{
	tinyxml2::XMLDocument doc;

	//Tries to load the file, quits if it fails
	if (doc.LoadFile(fileName.c_str()) != tinyxml2::XML_NO_ERROR)
	{
		GAME->LoadLevel(new LandingScreen);
		std::cout << "ERROR LOADING: " << fileName << "\nLOADING LANDING SCREEN...\n";

		return;
	}

	//Grabs first element
	tinyxml2::XMLElement * element = doc.RootElement();

	//set par
	par = element->IntAttribute("par");
	strokeCount = 0;

	int numLayers = 0;

	rotateLevel = false;
	isShooting = false;

	//Delete old main camera and set currentCamera to it.
	mainCamera->isFlagged = true;
	mainCamera = new GameCamera(this, Vec3(0, 0.75f, -7),Vec3::Zero() );
	currentCamera = mainCamera;

	//ADD GUI  **MUST BE BEFORE OTHER TEXTURES OR IT WON'T SHOW UP** <- for some reason...
	gui = new DIY_Level_GUI(this, par, HasObjectives());

	Models->CreateSkybox("skybox",		1000.0f);
	Models->loadTexture("skybox1",		"Images/skyboxUP.png");
	Models->loadTexture("layerGrid",	"Images/grid.png");

	Models->loadTexture("planet1",		"Images/aruba.tif");
	Models->loadTexture("planet2",		"Images/planet_Rim.tif");
	Models->loadTexture("planet3",		"Images/minersMoon.tif");
	Models->loadTexture("planet4",		"Images/planetTex.png");
	Models->loadTexture("planet5",		"Images/hoth.tif");

	Models->loadTexture("ballSkin",		"Images/8ball.png");
	Models->loadModel("sphere",			"Models/planet.obj", true);
	Models->loadModel("sun",			"Models/planet.obj", true);

	Models->loadModel("warpGate",		"Models/WarpGate.obj", true);
	Models->loadTexture("gateTexture",	"Images/rosary.png");

	Models->loadTexture("meteorTex1",	"Images/meteor_texture.tif");
	Models->loadTexture("meteorTex2",	"Images/meteor_texture_2.tif");
	Models->loadTexture("meteorTex3",	"Images/meteor_texture_3.tif");

	Models->loadTexture("sunTexture",	"Images/sun.tif");

	Models->loadModel("meteor1",		"Models/meteor_01.obj", true);
	Models->loadModel("meteor2",		"Models/meteor_02.obj", true);
	Models->loadModel("meteor3",		"Models/meteor_03.obj", true);

	//Load up and play the music for in-game
	Audio->loadMusic("gameTheme",		"Sounds/Exotics.wav");
	Audio->getMusic("gameTheme")->Play();

	Models->loadModel("wormhole",		"Models/wormhole.obj", true);
	Models->loadTexture("wormholeTexture", "Images/Galaxy.png");

	//Gotta be big to show up..
	//don't know why 
	const int texSize = 140 * 140 * 4;
	float pixelDataWhite[texSize];
	for (int i = 0; i < texSize; i++)
	{
		pixelDataWhite[i] = 1.0f;
	}
	Models->createTexture("white", pixelDataWhite, 1, 1);
	Models->loadModel("pointer", "Models/pointer.obj", true);

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

	//Setting level boundaries. CAN BE EDITTED
	levelBoundsX = 10;

	//set up skybox
	skybox = new GameObject(this, currentCamera->position);

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
				GameObject * objectivePlanet;

				float x = objectElement->FloatAttribute("x");
				float z = objectElement->FloatAttribute("z");

				if (objectElement->Attribute("type", "PlanetHorizontal")){

					std::string textureName = objectElement->Attribute("texture");

					//Get an XML element to find potential attached objective planets
					tinyxml2::XMLElement * objectiveElement;

					//Check if planet has attached objective
					if (objectElement->Attribute("objective"))
					{
						//Find first planet description in Objectives node
						objectiveElement = doc.RootElement()->FirstChildElement("Objectives")->FirstChildElement("Planet");

						//Search through all planets in Objectives until one with matching name is found
						while (*(objectElement->Attribute("objective")) != *(objectiveElement->Attribute("name")))
						{
							objectiveElement = objectiveElement->NextSiblingElement();

							//If you're at the end and not found it, break
							if (!objectiveElement)
								break;
						}

						//Now create the planet as well as the objective planet to be attached
						object = new PlanetHorizontal(this, Vec3(x, -2 + i * levelBoundsY, z), textureName);

						objectivePlanet = new ObjectivePlanet(this, object, objectiveElement->Attribute("texture"), ObjectivePlanet::Horizonal);
						objectiveCount++;
					}
					//Else just create the horizontal planet
					else
						object = new PlanetHorizontal(this, Vec3(x, -2 + i * levelBoundsY, z), textureName);



				}
				else if (objectElement->Attribute("type", "PlanetVertical")){
					std::string textureName = objectElement->Attribute("texture");

					tinyxml2::XMLElement * objectiveElement;

					//Check if planet has attached objective
					if (objectElement->Attribute("objective"))
					{
						//Find first planet description in Objectives node
						objectiveElement = doc.RootElement()->FirstChildElement("Objectives")->FirstChildElement("Planet");

						//Search through all planets in Objectives until one with matching name is found
						while (*(objectElement->Attribute("objective")) != *(objectiveElement->Attribute("name")))
						{
							objectiveElement = objectiveElement->NextSiblingElement();

							//If you're at the end and not found it, break
							if (!objectiveElement)
								break;
						}

						object = new PlanetVertical(this, Vec3(x, -2 + i * levelBoundsY, z), textureName);

						objectivePlanet = new ObjectivePlanet(this, object, objectiveElement->Attribute("texture"), ObjectivePlanet::Vertical);
						objectiveCount++;
					}
					else
					{

					}
					object = new PlanetVertical(this, Vec3(x, -2 + i * levelBoundsY, z), textureName);
				}
				else if (objectElement->Attribute("type", "Asteroids")){
					object = new AsteroidField(this, Vec3(x, -2 + i * levelBoundsY, z), 1, 4);
				}
				else if (objectElement->Attribute("type", "Wormhole")){
					object = new Wormhole(this, Vec3(x, -2 + i * levelBoundsY, z), objectElement->IntAttribute("destination"));
				}
				else if (objectElement->Attribute("type", "WarpGate")){
					object = new WarpGate(this, Vec3(x, -2 + i * levelBoundsY, z), Quat(1, 0, 0, 0));
				}
				else if (objectElement->Attribute("type", "Player1Start")){
					setPlayerLayer = true;

					object = new PlayerBall(this, Vec3(x, -2 + i * levelBoundsY, z));
					playerBall = object;
				}
				else if (objectElement->Attribute("type", "Sun"))
				{
					std::string textureName = objectElement->Attribute("texture");

					object = new Sun(this, Vec3(x, -2 + i * levelBoundsY, z), textureName);
				}
				else{

				}

				gameObjects.push_back(object);

				if (objectivePlanet)
					gameObjects.push_back(objectivePlanet);

				//point to next object element
				objectElement = objectElement->NextSiblingElement("Object");


			} while (objectElement);

			//create layer in the list
			layers.push_back(new Layer(this, Vec3(0, -2 + i * levelBoundsY, 0), gameObjects));

			//Attaches the plane collider to last layer added if it contains the players start point
			if (setPlayerLayer)
			{
				//layerRB = new GameObject(this, layers.back()->position);
				//new Rigidbody(layerRB, new PlaneCollider(layerRB, Vec3::BasisY()));
				//layerRB->getComponent<Rigidbody>()->isKinematic = false;

				planeRigidBody = new Rigidbody(*(layers.end() - 1), new PlaneCollider(*(layers.end() - 1), Vec3(0, 1, 0)));
				planeRigidBody->isKinematic = false;

				//PlaneCollider * p = new PlaneCollider(*(layers.end() - 1), Vec3(0, 1, 0));
				//(*(layers.end() - 1))->getComponent<Rigidbody>()->col = p;
				setPlayerLayer = false;
			}

			//Sets element pointer to the next layer

			element = element->NextSiblingElement("Layer");

			if (!element)break;

			objectElement = element->FirstChildElement("Object");
	}

	gui->SetObjectivesRemaining(HasObjectives());

	//Change camera to new focus camera
	mainCamera->isFlagged = true;
	mainCamera = new FocusCamera(this, playerBall, playerBall->position + Vec3(0,0,-7));
	currentCamera = mainCamera;	


	//Can now go through Update loop.
	hasFinishedLoading = true;
}

DIY_Level::~DIY_Level()
{
	delete gui;
}

int DIY_Level::HasObjectives()
{
	return objectiveCount;
}

void DIY_Level::LevelUpdate(float timeStep_)
{
	if (!hasFinishedLoading)
		return;

	Level::LevelUpdate(timeStep_);

	//Victory TEST
	if (InputController::getInstance()->isKeyDown(SDLK_v))
	{
		objectiveCount = 0;
		PlayerHasShotBallIntoSun = true;
	}

	//Game state switch
	switch (levelState)
	{
	case DIY_Level_State::PLAYING:
		gui->shotPower = ((PlayerBall*)playerBall)->GetChargePercent() / 100.0f;

		PauseLogic();

		//Check for Victory
		if (HasObjectives() == 0  && PlayerHasShotBallIntoSun)
		{
			levelState = DIY_Level_State::VICTORY;
		}
		else
		{
			switch (playingState)
			{
			case DIY_Level_Playing_State::SHOOTING:
				if (!isShooting && ((PlayerBall*)playerBall)->GetIsChargingStrike())
					isShooting = true;
				else if (isShooting && !((PlayerBall*)playerBall)->GetIsChargingStrike())
				{
					isShooting = false;
					strokeCount++;
					gui->PlayerTookAStroke();

					playingState = DIY_Level_Playing_State::WATCHING;
				}
				break;
			case DIY_Level_Playing_State::WATCHING:
				if (!playerBall->getComponent<Rigidbody>()->isAwake())
					playingState = DIY_Level_Playing_State::SHOOTING;
				break;
			}

			//if (Input->isMouseDown(SDL_BUTTON_RIGHT))
			//{
			//	//layerContainer->Rotate(Quat(Input->deltaMouse().x * timeStep_, Vec3(0, 1.0f, 0)));
			//	PhysicsWorld::Orbit(Vec3::Zero(), Vec3::BasisY(), mainCamera, Input->deltaMouse().x * timeStep_);
			//	mainCamera->Rotate(Quat(Input->deltaMouse().x * timeStep_, Vec3::BasisY()));
			//}
			//break;
		}
	case DIY_Level_State::PAUSED:
		PauseLogic();
		break;
	case DIY_Level_State::VICTORY:
		switch (victoryState)
		{
		case DIY_Level_Victory_State::REVIEW:
			break;
		case DIY_Level_Victory_State::LEVEL_SELECT:
			break;
		}
		break;
	}

	gui->Update(timeStep_);
}

void DIY_Level::SetLayerPlane(Layer * layer_)
{
	/*layerRB->position = layer_->position;
	static_cast<PlaneCollider*>(layerRB->getComponent<Collider>())->plane = Plane(Vec3::BasisY(), layer_->position);*/
	planeRigidBody->parentObject = layer_;
	planeRigidBody->col->parentObject = layer_;
	static_cast<PlaneCollider *>(planeRigidBody->col)->plane = Plane(Vec3(0, 1, 0), planeRigidBody->parentObject->position);
}

Layer * DIY_Level::GetLayerPlane()
{
	return (Layer *)planeRigidBody->parentObject;
}

void DIY_Level::PauseLogic()
{
	if (Input->isKeyDown(SDLK_ESCAPE) && !isPausedKeyStillPressed)
	{
		levelState = levelState == DIY_Level_State::PAUSED ? DIY_Level_State::PLAYING : DIY_Level_State::PAUSED;
		isPausedKeyStillPressed = true;
	}
	else if (!Input->isKeyDown(SDLK_ESCAPE) && isPausedKeyStillPressed)
	{
		isPausedKeyStillPressed = false;
	}

	PhysicsWorld::getInstance()->isPhysicsRunning = levelState == DIY_Level_State::PAUSED ? false : levelState == DIY_Level_State::VICTORY ? false : true;
}

void DIY_Level::AdjustObjectiveCount(int countChange_)
{
	objectiveCount += countChange_;
	gui->SetObjectivesRemaining(objectiveCount);
}

std::string  DIY_Level::GetLevelFileName()
{
	return fileName;
}

Vec2 DIY_Level::GetLevelBounds()
{
	return Vec2(levelBoundsX, levelBoundsY);
}