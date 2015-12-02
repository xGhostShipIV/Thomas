#include "ModelManager.h"
#include "Renderable.h"
#include "Texture.h"
#include "OpenGLUtilities.h"

#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

ModelManager * ModelManager::instance;

UINT32 ModelManager::nextTextureID = 0;
UINT32 ModelManager::nextModelID = 0;

GLuint ModelManager::transformLocation;
GLuint ModelManager::ambientLocation;
GLuint ModelManager::normalLocation;
GLuint ModelManager::materialLocation;

GLuint ModelManager::lightColor_Directional_Location;
GLuint ModelManager::lightDirection_Directional_Location;

GLuint ModelManager::lightColor_Point_Location;
GLuint ModelManager::lightPosition_Point_Location;

GLuint ModelManager::lightColor_Spot_Location;
GLuint ModelManager::lightPosition_Spot_Location;
GLuint ModelManager::lightDirection_Spot_Location;
GLuint ModelManager::lightAngle_Spot_Location;

GLuint ModelManager::isEffectedByLight_Location;
GLuint ModelManager::UI_DRAW_Location;


ModelManager::ModelManager(Render_Mode _render_mode)
{
	render_mode = _render_mode;

	if (_render_mode == RENDER_MODE_OPENGL)
	{
		program = GLU::UseShaders("testGame.vert", "testGame.frag");

		transformLocation = glGetUniformLocation(program, "Transform");
		normalLocation = glGetUniformLocation(program, "Normal");
		ambientLocation = glGetUniformLocation(program, "AmbientColor");
		materialLocation = glGetUniformLocation(program, "Material");

		lightColor_Directional_Location = glGetUniformLocation(program, "LightColor_Directional");
		lightDirection_Directional_Location = glGetUniformLocation(program, "LightDirection_Directional");

		lightColor_Point_Location = glGetUniformLocation(program, "LightColor_Point");
		lightPosition_Point_Location = glGetUniformLocation(program, "LightPosition_Point");

		lightColor_Spot_Location = glGetUniformLocation(program, "LightColor_Spot");
		lightPosition_Spot_Location = glGetUniformLocation(program, "LightPosition_Spot");
		lightDirection_Spot_Location = glGetUniformLocation(program, "LightDirection_Spot");
		lightAngle_Spot_Location = glGetUniformLocation(program, "LightAngle_Spot");

		isEffectedByLight_Location = glGetUniformLocation(program, "isEffectedByLight");
		UI_DRAW_Location = glGetUniformLocation(program, "uiDraw");
	}
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

void ModelManager::loadModel(string _id, string _fileName, bool _useModelTextureMap, Draw_Mode _mode)
{
	//Checks what our current render mode is and will create the appropriate
	//Renderable based on such. For example, will create an OpenGL_Renderable
	//if current render mode is for OpenGL

	Assimp::Importer import;
	const aiScene * scene;

	Renderable * model;

	switch (render_mode)
	{
	case ModelManager::Render_OpenGL:

		model = new OpenGL_Renderable();

		scene = import.ReadFile(_fileName, NULL);

		for (int i = 0; i < scene->mNumMeshes; i++)
		{
			Renderable::Mesh mesh;

			for (int j = 0; j < scene->mMeshes[i]->mNumVertices; j++)
			{
				Vec3 vertex = Vec3(scene->mMeshes[i]->mVertices[j].x, scene->mMeshes[i]->mVertices[j].y, scene->mMeshes[i]->mVertices[j].z);
				mesh.vertex.push_back(vertex);

				/*if (scene->mMeshes[i]->HasNormals())
				{
					Vec3 normal = Vec3(scene->mMeshes[i]->mNormals[j].x, scene->mMeshes[i]->mNormals[j].y, scene->mMeshes[i]->mNormals[j].z);
					mesh.normal.push_back(normal);
				}*/

				if (_useModelTextureMap && scene->mMeshes[i]->HasTextureCoords(0))
				{
					Vec2 texture = Vec2(scene->mMeshes[i]->mTextureCoords[0][j].x, scene->mMeshes[i]->mTextureCoords[0][j].y);
					mesh.textureMap.push_back(texture);
				}
			}

			model->meshes.push_back(mesh);
		}

		GenerateNormals(model);

		for (int m = 0; m < model->meshes.size(); m++)
		for (unsigned int i = 0; i < model->meshes[m].vertex.size(); i++)
				model->meshes[m].edge.push_back(i);

		
		for (int i = 0; i < scene->mNumMeshes; i++)
		{
			for (int j = 0; j < scene->mMeshes[i]->mNumFaces; j++)
			{
				model->meshes[i].face.push_back(scene->mMeshes[i]->mFaces[j].mNumIndices);
			}
		}

		if (!_useModelTextureMap)
			GenerateTextureMap(model);
		else
		{
			for (int m = 0; m < model->meshes.size(); m++)
			for (auto it = model->meshes[m].textureMap.begin(); it != model->meshes[m].textureMap.end(); it++)
			{
				masterTextureCoords.push_back(*it);
			}
		}


		/*if (model->normal.size() == 0)
		GenerateNormals(model);*/

		model->drawMode = _mode;

		InsertModel(model, _id);

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
	return models.find(GetModelID(_id))->second;
}

Renderable * ModelManager::getModel(UINT32 _id)
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

void ModelManager::CreateCuboid(string _id, float _w, float _h, float _l, bool _useCubeMap, float _uvRepeatX, float _uvRepeatY)
{
	Renderable * cube;
	Renderable::Mesh mesh;

	switch (render_mode)
	{
	case ModelManager::Render_OpenGL:

		cube = new OpenGL_Renderable();
		
		cube->meshes.push_back(mesh);

		/* Face Back */
		cube->meshes[0].vertex.push_back(Vec3(-_w, _h, _l));
		cube->meshes[0].vertex.push_back(Vec3(_w, _h, _l));
		cube->meshes[0].vertex.push_back(Vec3(_w, -_h, _l));
		cube->meshes[0].vertex.push_back(Vec3(-_w, -_h, _l));

		/* Face Front */
		cube->meshes[0].vertex.push_back(Vec3(-_w, -_h, -_l));
		cube->meshes[0].vertex.push_back(Vec3(_w, -_h, -_l));
		cube->meshes[0].vertex.push_back(Vec3(_w, _h, -_l));
		cube->meshes[0].vertex.push_back(Vec3(-_w, _h, -_l));
		/* Face Left */
		cube->meshes[0].vertex.push_back(cube->meshes[0].vertex[0]);
		cube->meshes[0].vertex.push_back(cube->meshes[0].vertex[3]);
		cube->meshes[0].vertex.push_back(cube->meshes[0].vertex[4]);
		cube->meshes[0].vertex.push_back(cube->meshes[0].vertex[7]);
		/* Face Right */
		cube->meshes[0].vertex.push_back(cube->meshes[0].vertex[6]);
		cube->meshes[0].vertex.push_back(cube->meshes[0].vertex[5]);
		cube->meshes[0].vertex.push_back(cube->meshes[0].vertex[2]);
		cube->meshes[0].vertex.push_back(cube->meshes[0].vertex[1]);
		/* Face Top */
		cube->meshes[0].vertex.push_back(cube->meshes[0].vertex[7]);
		cube->meshes[0].vertex.push_back(cube->meshes[0].vertex[6]);
		cube->meshes[0].vertex.push_back(cube->meshes[0].vertex[1]);
		cube->meshes[0].vertex.push_back(cube->meshes[0].vertex[0]);
		/* Face Bottom */
		cube->meshes[0].vertex.push_back(cube->meshes[0].vertex[3]);
		cube->meshes[0].vertex.push_back(cube->meshes[0].vertex[2]);
		cube->meshes[0].vertex.push_back(cube->meshes[0].vertex[5]);
		cube->meshes[0].vertex.push_back(cube->meshes[0].vertex[4]);


		///* Face Back */		cube->edge.push_back(0);	cube->edge.push_back(1);	cube->edge.push_back(2);	cube->edge.push_back(3);
		///* Face Front */		cube->edge.push_back(4);	cube->edge.push_back(5);	cube->edge.push_back(6);	cube->edge.push_back(7);
		///* Face Left */		cube->edge.push_back(0);	cube->edge.push_back(3);	cube->edge.push_back(4);	cube->edge.push_back(7);
		///* Face Right */		cube->edge.push_back(6);	cube->edge.push_back(5);	cube->edge.push_back(2);	cube->edge.push_back(1);
		///* Face Top */		cube->edge.push_back(7);	cube->edge.push_back(6);	cube->edge.push_back(1);	cube->edge.push_back(0);
		///* Face Bottom */		cube->edge.push_back(3);	cube->edge.push_back(2);	cube->edge.push_back(5);	cube->edge.push_back(4);

		for (unsigned int i = 0; i < cube->meshes[0].vertex.size(); i++)
			cube->meshes[0].edge.push_back(i);

		for (int i = 0; i < 6; i++)
			cube->meshes[0].face.push_back(4);

		GenerateNormals(cube);

		if (!_useCubeMap)
			GenerateTextureMap(cube, _uvRepeatX, _uvRepeatY);
		else
			GenerateCubeMap(cube);

		InsertModel(cube, _id);

		break;
	case ModelManager::Render_DirectX:
		break;
	case ModelManager::Render_Ogre:
		break;
	}
}

void ModelManager::CreateSkybox(string _id, float _size, bool _normalsOnBottom)
{
	Renderable * skybox;
	Renderable::Mesh mesh;

	switch (render_mode)
	{
	case ModelManager::Render_OpenGL:

		skybox = new OpenGL_Renderable();
		skybox->meshes.push_back(mesh);

		/* Face Back  */
		skybox->meshes[0].vertex.push_back(Vec3(-_size, -_size, _size)); //3
		skybox->meshes[0].vertex.push_back(Vec3(_size, -_size, _size)); //2
		skybox->meshes[0].vertex.push_back(Vec3(_size, _size, _size)); //1
		skybox->meshes[0].vertex.push_back(Vec3(-_size, _size, _size)); //0

		/* Face Front */
		skybox->meshes[0].vertex.push_back(Vec3(-_size, _size, -_size)); //7
		skybox->meshes[0].vertex.push_back(Vec3(_size, _size, -_size)); //6
		skybox->meshes[0].vertex.push_back(Vec3(_size, -_size, -_size)); //5
		skybox->meshes[0].vertex.push_back(Vec3(-_size, -_size, -_size)); //4

		/* Face Left */
		skybox->meshes[0].vertex.push_back(skybox->meshes[0].vertex[0]);
		skybox->meshes[0].vertex.push_back(skybox->meshes[0].vertex[3]);
		skybox->meshes[0].vertex.push_back(skybox->meshes[0].vertex[4]);
		skybox->meshes[0].vertex.push_back(skybox->meshes[0].vertex[7]);
		/* Face Right */
		skybox->meshes[0].vertex.push_back(skybox->meshes[0].vertex[6]);
		skybox->meshes[0].vertex.push_back(skybox->meshes[0].vertex[5]);
		skybox->meshes[0].vertex.push_back(skybox->meshes[0].vertex[2]);
		skybox->meshes[0].vertex.push_back(skybox->meshes[0].vertex[1]);
		/* Face Top */
		skybox->meshes[0].vertex.push_back(skybox->meshes[0].vertex[7]);
		skybox->meshes[0].vertex.push_back(skybox->meshes[0].vertex[6]);
		skybox->meshes[0].vertex.push_back(skybox->meshes[0].vertex[1]);
		skybox->meshes[0].vertex.push_back(skybox->meshes[0].vertex[0]);
		/* Face Bottom */
		skybox->meshes[0].vertex.push_back(skybox->meshes[0].vertex[3]);
		skybox->meshes[0].vertex.push_back(skybox->meshes[0].vertex[2]);
		skybox->meshes[0].vertex.push_back(skybox->meshes[0].vertex[5]);
		skybox->meshes[0].vertex.push_back(skybox->meshes[0].vertex[4]);

		for (unsigned int i = 0; i < skybox->meshes[0].vertex.size(); i++)
			skybox->meshes[0].edge.push_back(i);

		for (int i = 0; i < 6; i++)
			skybox->meshes[0].face.push_back(4);

		GenerateNormals(skybox, true, _normalsOnBottom);
		GenerateCubeMap(skybox);

		InsertModel(skybox, _id);

		break;
	case ModelManager::Render_DirectX:
		break;
	case ModelManager::Render_Ogre:
		break;
	}
}

void ModelManager::CreatePyramid(string _id, float _w, float _h, float _l, float _uvRepeatX, float _uvRepeatY)
{
	Renderable * pyramid;
	Renderable::Mesh mesh;

	switch (render_mode)
	{
	case ModelManager::Render_OpenGL:

		pyramid = new OpenGL_Renderable();
		pyramid->meshes.push_back(mesh);

		pyramid->meshes[0].vertex.push_back(Vec3(_w, 0.0f, -_l));
		pyramid->meshes[0].vertex.push_back(Vec3(-_w, 0.0f, -_l));
		pyramid->meshes[0].vertex.push_back(Vec3(-_w, 0.0f, _l));
		pyramid->meshes[0].vertex.push_back(Vec3(_w, 0.0f, _l));

		pyramid->meshes[0].vertex.push_back(Vec3(0.0f, _h, 0.0f));
		pyramid->meshes[0].vertex.push_back(pyramid->meshes[0].vertex[3]);
		pyramid->meshes[0].vertex.push_back(pyramid->meshes[0].vertex[2]);

		pyramid->meshes[0].vertex.push_back(pyramid->meshes[0].vertex[4]);
		pyramid->meshes[0].vertex.push_back(pyramid->meshes[0].vertex[2]);
		pyramid->meshes[0].vertex.push_back(pyramid->meshes[0].vertex[1]);

		pyramid->meshes[0].vertex.push_back(pyramid->meshes[0].vertex[4]);
		pyramid->meshes[0].vertex.push_back(pyramid->meshes[0].vertex[1]);
		pyramid->meshes[0].vertex.push_back(pyramid->meshes[0].vertex[0]);

		pyramid->meshes[0].vertex.push_back(pyramid->meshes[0].vertex[4]);
		pyramid->meshes[0].vertex.push_back(pyramid->meshes[0].vertex[0]);
		pyramid->meshes[0].vertex.push_back(pyramid->meshes[0].vertex[3]);

		////	/* Bottom */pyramid->edge.push_back(0);	 pyramid->edge.push_back(1);	pyramid->edge.push_back(2);		pyramid->edge.push_back(3);
		////	/* Face 1 */pyramid->edge.push_back(0);	 pyramid->edge.push_back(1);	pyramid->edge.push_back(4);
		////	/* Face 2 */pyramid->edge.push_back(1);	 pyramid->edge.push_back(2);	pyramid->edge.push_back(4);
		////	/* Face 3 */pyramid->edge.push_back(2);	 pyramid->edge.push_back(3);	pyramid->edge.push_back(4);
		////	/* Face 4 */pyramid->edge.push_back(3);	 pyramid->edge.push_back(0);	pyramid->edge.push_back(4);

		for (unsigned int i = 0; i < pyramid->meshes[0].vertex.size(); i++)
			pyramid->meshes[0].edge.push_back(i);

		pyramid->meshes[0].face.push_back(4);
		for (int i = 1; i < 5; i++)pyramid->meshes[0].face.push_back(3);

		GenerateNormals(pyramid);
		GenerateTextureMap(pyramid, _uvRepeatX, _uvRepeatY);

		InsertModel(pyramid, _id);

		break;
	case ModelManager::Render_DirectX:
		break;
	case ModelManager::Render_Ogre:
		break;
	default:
		break;
	}
}

void ModelManager::CreatePlane(string _id, float _h, float _w, float _uvRepeatX, float _uvRepeatY)
{
	Renderable * plane;
	Renderable::Mesh mesh;

	switch (render_mode)
	{
	case ModelManager::Render_OpenGL:

		plane = new OpenGL_Renderable();
		plane->meshes.push_back(mesh);

		_h /= 2.0f;
		_w /= 2.0f;

		plane->meshes[0].vertex.push_back(Vec3(-_w, _h, 0.0f));
		plane->meshes[0].vertex.push_back(Vec3(_w, _h, 0.0f));
		plane->meshes[0].vertex.push_back(Vec3(_w, -_h, 0.0f));
		plane->meshes[0].vertex.push_back(Vec3(-_w, -_h, 0.0f));

		for (unsigned int i = 0; i < plane->meshes[0].vertex.size(); i++)
			plane->meshes[0].edge.push_back(i);

		for (int i = 0; i < 1; i++)
			plane->meshes[0].face.push_back(4);

		GenerateNormals(plane);
		GenerateTextureMap(plane, _uvRepeatX, _uvRepeatY);

		InsertModel(plane, _id);

		break;
	case ModelManager::Render_DirectX:
		break;
	case ModelManager::Render_Ogre:
		break;
	default:
		break;
	}
}

void ModelManager::CreateSquare(string _id, float _w, float _h, float _uvRepeatX, float _uvRepeatY)
{
	Renderable * square;
	Renderable::Mesh mesh;

	switch (render_mode)
	{
	case ModelManager::Render_OpenGL:

		square = new OpenGL_Renderable();
		square->meshes.push_back(mesh);

		square->meshes[0].vertex.push_back(Vec3(_w / 2.0f, _h / 2.0f, 0));
		square->meshes[0].vertex.push_back(Vec3(-_w / 2.0f, _h / 2.0f, 0));
		square->meshes[0].vertex.push_back(Vec3(-_w / 2.0f, -_h / 2.0f, 0));
		square->meshes[0].vertex.push_back(Vec3(_w / 2.0f, -_h / 2.0f, 0));

		for (unsigned int i = 0; i < square->meshes[0].vertex.size(); i++)
			square->meshes[0].edge.push_back(i);

		square->meshes[0].face.push_back(4);

		GenerateNormals(square);
		GenerateTextureMap(square, _uvRepeatX, _uvRepeatY);

		InsertModel(square, _id);

		break;
	case ModelManager::Render_DirectX:
		break;
	case ModelManager::Render_Ogre:
		break;
	default:
		break;
	}
}

void ModelManager::InsertModel(Renderable* _renderable, string _id)
{

	models.insert(std::pair<UINT32, Renderable *>(nextModelID, _renderable));
	modelMap.insert(std::pair<string, int>(_id, nextModelID));
	nextModelID++;

	for (int m = 0; m < _renderable->meshes.size(); m++)
	{
		_renderable->meshes[m].offsetVertex = masterVectorList.size();

		for (auto it = _renderable->meshes[m].vertex.begin(); it != _renderable->meshes[m].vertex.end(); it++)
		{
			masterVectorList.push_back(*it);
		}

		for (int i = 0; i < _renderable->meshes[m].edge.size(); i++)
			_renderable->meshes[m].edge[i] += _renderable->meshes[m].offsetVertex;
	}
}

void ModelManager::GenerateTextureMap(Renderable* _renderable, float _uvRepeatX, float _uvRepeatY)
{
	for (int m = 0; m < _renderable->meshes.size(); m++)
	{
		for (int i = 0; i < _renderable->meshes[m].face.size(); i++)
		{						
			if (_renderable->meshes[m].face[i] == 4)
				_renderable->meshes[m].textureMap.push_back(Vec2(0, 0));

			_renderable->meshes[m].textureMap.push_back(Vec2(_uvRepeatX, 0));
			_renderable->meshes[m].textureMap.push_back(Vec2(_uvRepeatX, _uvRepeatY));
			_renderable->meshes[m].textureMap.push_back(Vec2(0, _uvRepeatY));
			
		}

		for (auto it = _renderable->meshes[m].textureMap.begin(); it != _renderable->meshes[m].textureMap.end(); it++)
		{
			masterTextureCoords.push_back(*it);
		}
	}
}

void  ModelManager::GenerateCubeMap(Renderable* _renderable)
{
	//Generate Cubemap 
	{
		//Back
		_renderable->meshes[0].textureMap.push_back(Vec2(0.25f, 1 / 3.0f));
		_renderable->meshes[0].textureMap.push_back(Vec2(0.5f, 1 / 3.0f));
		_renderable->meshes[0].textureMap.push_back(Vec2(0.5f, 2 / 3.0f));
		_renderable->meshes[0].textureMap.push_back(Vec2(0.25f, 2 / 3.0f));

		//Front
		_renderable->meshes[0].textureMap.push_back(Vec2(1, 2 / 3.0f));
		_renderable->meshes[0].textureMap.push_back(Vec2(0.75f, 2 / 3.0f));
		_renderable->meshes[0].textureMap.push_back(Vec2(0.75f, 1 / 3.0f));
		_renderable->meshes[0].textureMap.push_back(Vec2(1, 1 / 3.0f));

		//Right
		_renderable->meshes[0].textureMap.push_back(Vec2(0.25f, 1 / 3.0f));//3
		_renderable->meshes[0].textureMap.push_back(Vec2(0.25f, 2 / 3.0f));//4
		_renderable->meshes[0].textureMap.push_back(Vec2(0, 2 / 3.0f));//1
		_renderable->meshes[0].textureMap.push_back(Vec2(0, 1 / 3.0f));//2

		//Left
		_renderable->meshes[0].textureMap.push_back(Vec2(0.75f, 1 / 3.0f));//3
		_renderable->meshes[0].textureMap.push_back(Vec2(0.75f, 2 / 3.0f));//4
		_renderable->meshes[0].textureMap.push_back(Vec2(0.50f, 2 / 3.0f));//1
		_renderable->meshes[0].textureMap.push_back(Vec2(0.50f, 1 / 3.0f));//2

		//Top  ?
		_renderable->meshes[0].textureMap.push_back(Vec2(0.25f, 0));
		_renderable->meshes[0].textureMap.push_back(Vec2(0.50f, 0));
		_renderable->meshes[0].textureMap.push_back(Vec2(0.50f, 1 / 3.0f));
		_renderable->meshes[0].textureMap.push_back(Vec2(0.25f, 1 / 3.0f));
		
		//Bottom  ?
		_renderable->meshes[0].textureMap.push_back(Vec2(0.25f, 2 / 3.0f));
		_renderable->meshes[0].textureMap.push_back(Vec2(0.50f, 2 / 3.0f));
		_renderable->meshes[0].textureMap.push_back(Vec2(0.50f, 1));
		_renderable->meshes[0].textureMap.push_back(Vec2(0.25f, 1));
	}

	for (auto it = _renderable->meshes[0].textureMap.begin(); it != _renderable->meshes[0].textureMap.end(); it++)
	{
		masterTextureCoords.push_back(*it);
	}
}

void ModelManager::GenerateNormals(Renderable* _renderable, bool _reverse, bool _normalsOnBottom)
{
	for (int m = 0; m < _renderable->meshes.size(); m++)
	{
		int offset = 0;

		for (int i = 0; i < _renderable->meshes[m].face.size(); i++)
		{
			Vec3 normal;

			if (!_normalsOnBottom)
			{

				Vec3 p1 = _renderable->meshes[m].vertex[_renderable->meshes[m].edge[offset]];
				Vec3 p2 = _renderable->meshes[m].vertex[_renderable->meshes[m].edge[offset + 1]];
				Vec3 p3 = _renderable->meshes[m].vertex[_renderable->meshes[m].edge[offset + 2]];

				Vec3 A = p1 - p2;
				Vec3 B = p2 - p3;

				normal = Vec3::cross(A, B).Normalized();

				float dotP = Vec3::dot(p1, normal);

				if (Vec3::dot(p1, normal) > 0)
					normal *= -1;
			}
			else
				normal = Vec3(0, 1, 0);

			if (_reverse)
				normal *= -1;

			_renderable->meshes[m].normal.push_back(normal);

			offset += _renderable->meshes[m].face[i];
		}
	}
}

#define BUFFER_OFFSET(i) ((void*)(i))
void ModelManager::PushModels()
{
	/*  VERTICES  */

	//Push vertex to GPU
	glGenVertexArrays(1, VAOs);
	glBindVertexArray(VAOs[0]);

	glGenBuffers(2, Buffers);

	if (masterVectorList.size() > 0)
	{
		int arraySize = masterVectorList.size() * 3 * 4; //Each vector contains 3 floats (which are 4 bytes)
		float * newMasterList = new float[masterVectorList.size() * 3];

		//populate vector list
		for (int i = 0; i < masterVectorList.size(); i++)
		{
			newMasterList[i * 3] = masterVectorList[i].x;
			newMasterList[3 * i + 1] = masterVectorList[i].y;
			newMasterList[3 * i + 2] = masterVectorList[i].z;
		}

		glBindBuffer(GL_ARRAY_BUFFER, Buffers[0]);
		glBufferData(GL_ARRAY_BUFFER, arraySize, newMasterList, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
		glEnableVertexAttribArray(0);

		delete newMasterList;
	}

	/*  TEXTURES  */
	GLuint* textureArray = new GLuint[textures.size()];
	glGenTextures(textures.size(), textureArray);

	//Pass texture id to textures
	int i = 0;
	for (auto it = textures.begin(); it != textures.end(); it++)
	{
		it->second->address = textureArray[i];

		glBindTexture(GL_TEXTURE_2D, it->second->address);

		switch (it->second->dataType)
		{
		case Texture::TextureDataType::Float:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, it->second->width, it->second->height, 0, GL_RGBA, GL_FLOAT, it->second->pixelData);
			break;
		case Texture::TextureDataType::UnsignedByte:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, it->second->width, it->second->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, it->second->pixelData);
			break;
		}

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		i++;
	}
	delete textureArray;

	if (masterTextureCoords.size() > 0)
	{
		float * newMasterTextureList = new float[masterTextureCoords.size() * 2];
		for (int i = 0; i < masterTextureCoords.size(); i++)
		{
			newMasterTextureList[2 * i + 0] = masterTextureCoords[i].x;
			newMasterTextureList[2 * i + 1] = masterTextureCoords[i].y;
		}

		glBindBuffer(GL_ARRAY_BUFFER, Buffers[1]);
		glBufferData(GL_ARRAY_BUFFER, masterTextureCoords.size() * 2 * 4, newMasterTextureList, GL_STATIC_DRAW);
		glBindAttribLocation(program, 1, "vTexCoord");
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
		glEnableVertexAttribArray(1);

		delete newMasterTextureList;
	}
}

void ModelManager::createTexture(string _id, float* _pixelData, UINT32 _textureWidth, UINT32 _textureHeight)
{
	textures.insert(std::pair<int, Texture*>(nextTextureID, new Texture(_pixelData, _textureWidth, _textureHeight)));
	textureMap.insert(std::pair<string, int>(_id, nextTextureID));

	nextTextureID++;
}

void ModelManager::loadTexture(string _id, string _fileName)
{
	SDL_Surface *texture = IMG_Load(_fileName.c_str());

	if (texture == NULL)		{
		printf("Image failed to load! SDL_image Error: %s\n", IMG_GetError());
		return;
	}

	Texture * t = new Texture(texture);
	textures.insert(std::pair<UINT32, Texture*>(nextTextureID, t));
	textureMap.insert(std::pair<string, UINT32>(_id, nextTextureID));

	nextTextureID++;
}

Texture* ModelManager::getTexture(string _id)
{
	return textures.find(GetTextureID(_id))->second;
}

Texture* ModelManager::getTexture(UINT32 _id)
{
	return textures.find(_id)->second;
}

UINT32 ModelManager::GetModelID(string _name)
{
	return modelMap.find(_name)->second;
}

UINT32 ModelManager::GetTextureID(string _name)
{
	return textureMap.find(_name)->second;
}