#pragma once
#include <string>
#include <vector>
#include <map>
#include "../Math/four_dimensions.hpp"
#include <glew.h>
#include "OpenGLUtilities.h"

#define RENDER_MODE_OPENGL ModelManager::Render_OpenGL
#define RENDER_MODE_DIRECTX ModelManager::Render_DirectX
#define RENDER_MODE_OGRE ModelManager::Render_Ogre

class Renderable;

//So I dont have to type out std::string
typedef std::string string;

class ModelManager
{
	friend class RenderableComponent;
	friend class Camera;

	//An enumeration to set which graphics engine is being used
	enum Render_Mode{
		Render_OpenGL,
		Render_DirectX,
		Render_Ogre
	};

public:
	~ModelManager();

	static GLuint colourLocation, transformLocation;

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

	//called to delete all models in memory and clear the model map
	void unloadModels();

	//Pushed all model information to the GPU
	void PushModels();

	/* PRIMITIVE FACTORY METHODS */
	void CreateCuboid(string _id, float _h, float _w, float _l);
	void CreateSphere(string _id, float _r){}
	void CreatePyramid(string _id, float _w, float _l, float _h){}
	void CreateCone(string _id, float _r, float _h){}
	void CreateCylinder(string _id, float _r, float _h){}

	GLuint GetProgramID()
	{ 
		return program; 
	}

private:
	ModelManager(Render_Mode = Render_OpenGL);

	//Goes into the model map and returns a pointer to the renderable
	//with the given tag
	Renderable * getModel(string _id);

	//stores the current render mode for initialization of renderables
	Render_Mode render_mode;

	//The map to store all models
	std::map<string, Renderable *> models;

	//The master Vector list that will ultimately be pushed to the GPU
	std::vector<Vec3> masterVectorList;

	//Shaders Location
	GLuint program;
	GLuint VAOs[1];
	GLuint Buffers[1];
};

