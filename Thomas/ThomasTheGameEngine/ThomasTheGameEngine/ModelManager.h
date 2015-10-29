#pragma once
#include <string>
#include <map>

#define RENDER_MODE_OPENGL ModelManager::Render_OpenGL
#define RENDER_MODE_DIRECTX ModelManager::Render_DirectX
#define RENDER_MODE_OGRE ModelManager::Render_Ogre

class Renderable;

//So I dont have to type out std::string
typedef std::string string;

class ModelManager
{
	//An enumeration to set which graphics engine is being used
	enum Render_Mode{
		Render_OpenGL,
		Render_DirectX,
		Render_Ogre
	};

public:
	~ModelManager();

	//A static pointer to an instance of the manager
	static ModelManager * instance;

	//Returns a pointer to a ModelManager. Render mode defaults to openGL if none specified
	//Whatever you pass wont matter if instance is not null
	static ModelManager * getInstance(Render_Mode _renderMode = Render_OpenGL){
		if (!instance)instance = new ModelManager(_renderMode);
		return instance;
	}

	//called to set the render mode
	void setRenderMode(Render_Mode _renderMode);

	//Creates a renderable based on the given COLLADA file and inserts
	//it into the map of models with the _id as its string
	void loadModel(string _id, string _fileName);

	//Goes into the model map and returns a pointer to the renderable
	//with the given tag
	Renderable * getModel(string _id);

	//called to delete all models in memory and clear the model map
	void unloadModels();

private:
	ModelManager(Render_Mode = Render_OpenGL);

	//stores the current render mode for initialization of renderables
	Render_Mode render_mode;

	//The map to store all models
	std::map<string, Renderable *> models;
};

