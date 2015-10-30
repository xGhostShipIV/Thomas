#include "ModelManager.h"
#include "Renderable.h"

ModelManager * ModelManager::instance;

ModelManager::ModelManager(Render_Mode _render_mode)
{
	render_mode = _render_mode;
}


ModelManager::~ModelManager()
{
	//deletes all models still in memory
	for (auto it = models.begin(); it != models.end(); it++)
	{
		delete it->second;
	}

	models.clear();
}

void ModelManager::loadModel(string _id, string _fileName)
{
	//Checks what our current render mode is and will create the appropriate
	//Renderable based on such. For example, will create an OpenGL_Renderable
	//if current render mode is for OpenGL
	switch (render_mode)
	{
	case ModelManager::Render_OpenGL:
		break;
	case ModelManager::Render_DirectX:
		break;
	case ModelManager::Render_Ogre:
		break;
	default:
		break;
	}
}

Renderable * ModelManager::getModel(string _id)
{
	return models.find(_id)->second;
}

void ModelManager::unloadModels()
{
	//deletes all models still in memory
	for (auto it = models.begin(); it != models.end(); it++)
	{
		delete it->second;
	}

	models.clear();
}

void ModelManager::setRenderMode(ModelManager::Render_Mode _rm)
{
	render_mode = _rm;
}

void ModelManager::CreateCuboid(string _id, float _h, float _w, float _l)
{
	Renderable * cube;

	switch (render_mode)
	{
	case ModelManager::Render_OpenGL:
		
		cube = new OpenGL_Renderable();

		cube->vertex[0] = Vec3(_w, _h, _l);
		cube->vertex[1] = Vec3(_w, _h, -_l);
		cube->vertex[2] = Vec3(_w, -_h, _l);
		cube->vertex[3] = Vec3(_w, -_h, -_l);
		cube->vertex[4] = Vec3(-_w, _h, _l);
		cube->vertex[5] = Vec3(-_w, _h, -_l);
		cube->vertex[6] = Vec3(-_w, -_h, _l);
		cube->vertex[7] = Vec3(-_w, -_h, -_l);



		//Face 1				//Face 2				//Face 3				//Face 4				//Face 5				//Face 6
		cube->face[0] = 0;		cube->face[4] = 4;		cube->face[8] = 0;		cube->face[12] = 1;		cube->face[16] = 0;		cube->face[20] = 3;
		cube->face[1] = 1;		cube->face[5] = 5;		cube->face[9] = 3;		cube->face[13] = 2;		cube->face[17] = 1;		cube->face[21] = 2;
		cube->face[2] = 2;		cube->face[6] = 6;		cube->face[10] = 7;		cube->face[14] = 6;		cube->face[18] = 5;		cube->face[22] = 6;
		cube->face[3] = 3;		cube->face[7] = 7;		cube->face[11] = 4;		cube->face[15] = 5;		cube->face[19] = 4;		cube->face[23] = 7;

		
		models.insert(std::pair<string, Renderable *>("cuboid", cube));
		cube->offsetVertex = masterVectorList.size();
		
		for (auto it = cube->vertex.begin(); it != cube->vertex.end(); it++)
		{
			masterVectorList.push_back(*it);
		}

		break;
	case ModelManager::Render_DirectX:
		break;
	case ModelManager::Render_Ogre:
		break;
	}
}
