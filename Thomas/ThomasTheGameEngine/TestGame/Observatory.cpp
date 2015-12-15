#include "Observatory.h"
#include <ModelManager.h>
#include <AudioManager.h>
#include <FontManager.h>
#include <Label.h>


Observatory::Observatory()
{
	currentCamera->position = Vec3(0, 0, -5);

	SetAmbientColor(Colour(0.2,0.2,0.2));

	ModelManager::getInstance()->CreatePlane("plane", 1, 1);
	ModelManager::getInstance()->CreatePlane("surface", 1, 1, 3, 1);
	ModelManager::getInstance()->CreateSkybox("skybox", 10);
	ModelManager::getInstance()->CreateCuboid("doorModel", 0.25f, 0.5f, 0.05f);
	ModelManager::getInstance()->loadModel("meteor1", "Models/meteor_01.obj", true);
	ModelManager::getInstance()->loadModel("meteor2", "Models/meteor_02.obj", true);
	ModelManager::getInstance()->loadModel("meteor3", "Models/meteor_03.obj", true);
	ModelManager::getInstance()->loadModel("planet", "Models/planet.obj", true);
	ModelManager::getInstance()->loadModel("planet2", "Models/planet.obj", true);


	ModelManager::getInstance()->loadTexture("floor", "Images/dungeonFloor.tif");
	ModelManager::getInstance()->loadTexture("wall", "Images/dungeonWall.tif");
	ModelManager::getInstance()->loadTexture("space", "Images/spaceSkybox.tif");
	ModelManager::getInstance()->loadTexture("door", "Images/door.png");
	ModelManager::getInstance()->loadTexture("footprint", "Images/footprint.png");
	ModelManager::getInstance()->loadTexture("layerGrid", "Images/grid.png");
	ModelManager::getInstance()->loadTexture("meteorTex1", "Images/meteor_texture.tif");
	ModelManager::getInstance()->loadTexture("meteorTex2", "Images/meteor_texture_2.tif");
	ModelManager::getInstance()->loadTexture("meteorTex3", "Images/meteor_texture_3.tif");
	ModelManager::getInstance()->loadTexture("planetTex", "Images/hoth.tif");
	ModelManager::getInstance()->loadTexture("planetTex1", "Images/PlanetTex.png");
	ModelManager::getInstance()->loadTexture("sunTex", "Images/sun.tif");
	ModelManager::getInstance()->loadTexture("aruba", "Images/aruba.tif");
	ModelManager::getInstance()->loadTexture("Rim", "Images/planet_Rim.tif");
	ModelManager::getInstance()->loadTexture("minerMoon", "Images/minersMoon.tif");
	ModelManager::getInstance()->loadTexture("8ball", "Images/Ball8.tif");



	AudioManager::getInstance()->loadMusic("observatory", "Sounds/observatory-loop.wav");
	AudioManager::getInstance()->setMusicVolume(0.0f);


	FontManager::getInstance()->GenerateFont("font", 14, "Font/DroidSans.ttf");
	new Label(this, "Project: Thomas Engine Demo", Vec2(0.6, -0.9), FontManager::getInstance()->GetFont("font"), Colour::White());

	player = new Player(this, currentCamera);
	hallway = new Hallway(this, Vec3::Zero());
	obr = new ObservatoryRoom(this, Vec3(0, 0, 15), player);
	door = new SlidingDoor(this, Vec3(0, 0, 4.9f), player);

	ModelManager::getInstance()->PushModels();
}

Observatory::~Observatory()
{
}