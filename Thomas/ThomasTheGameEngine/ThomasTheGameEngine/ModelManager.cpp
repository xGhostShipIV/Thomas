#include "ModelManager.h"
#include "Renderable.h"
#include "Texture.h"
#include "OpenGLUtilities.h"

ModelManager * ModelManager::instance;
GLuint ModelManager::colourLocation;
GLuint ModelManager::transformLocation;

ModelManager::ModelManager(Render_Mode _render_mode)
{
	render_mode = _render_mode;

	if (_render_mode == RENDER_MODE_OPENGL)
	{
		GLU::OutputOpenGLVersion();
		program = GLU::UseShaders("testGame.vert", "testGame.frag");

		colourLocation = glGetUniformLocation(program, "fColor");
		transformLocation = glGetUniformLocation(program, "Transform");
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

		cube->vertex.push_back(Vec3(-_w, _h, _l));
		cube->vertex.push_back(Vec3(_w, _h, _l));
		cube->vertex.push_back(Vec3(_w, -_h, _l));
		cube->vertex.push_back(Vec3(-_w, -_h, _l));

		cube->vertex.push_back(Vec3(-_w, _h, -_l));
		cube->vertex.push_back(Vec3(_w, _h, -_l));
		cube->vertex.push_back(Vec3(_w, -_h, -_l));
		cube->vertex.push_back(Vec3(-_w, -_h, -_l));

		cube->vertex.push_back(cube->vertex[0]);
		cube->vertex.push_back(cube->vertex[3]);
		cube->vertex.push_back(cube->vertex[7]);
		cube->vertex.push_back(cube->vertex[4]);

		cube->vertex.push_back(cube->vertex[1]);
		cube->vertex.push_back(cube->vertex[2]);
		cube->vertex.push_back(cube->vertex[6]);
		cube->vertex.push_back(cube->vertex[5]);

		cube->vertex.push_back(cube->vertex[0]);
		cube->vertex.push_back(cube->vertex[1]);
		cube->vertex.push_back(cube->vertex[5]);
		cube->vertex.push_back(cube->vertex[4]);

		cube->vertex.push_back(cube->vertex[3]);
		cube->vertex.push_back(cube->vertex[2]);
		cube->vertex.push_back(cube->vertex[6]);
		cube->vertex.push_back(cube->vertex[7]);
		
		
		////	/* Face 1 */	cube->edge.push_back(0);	cube->edge.push_back(1);	cube->edge.push_back(2);	cube->edge.push_back(3);
		////	/* Face 2 */	cube->edge.push_back(4);	cube->edge.push_back(5);	cube->edge.push_back(6);	cube->edge.push_back(7);
		////	/* Face 3 */	cube->edge.push_back(0);	cube->edge.push_back(3);	cube->edge.push_back(7);	cube->edge.push_back(4);
		////	/* Face 4 */	cube->edge.push_back(1);	cube->edge.push_back(2);	cube->edge.push_back(6);	cube->edge.push_back(5);
		////	/* Face 5 */	cube->edge.push_back(0);	cube->edge.push_back(1);	cube->edge.push_back(5);	cube->edge.push_back(4);
		////	/* Face 6 */	cube->edge.push_back(3);	cube->edge.push_back(2);	cube->edge.push_back(6);	cube->edge.push_back(7);

		for (unsigned int i = 0; i < cube->vertex.size(); i++)
			cube->edge.push_back(i);

		for (int i = 0; i < 6; i++)
			cube->face.push_back(4);

		GenerateTextureMap(cube, _id);

		InsertModel(cube, _id);

		break;
	case ModelManager::Render_DirectX:
		break;
	case ModelManager::Render_Ogre:
		break;
	}
}

void ModelManager::CreatePyramid(string _id, float _w, float _l, float _h)
{
	Renderable * pyramid;

	switch (render_mode)
	{
	case ModelManager::Render_OpenGL:

		pyramid = new OpenGL_Renderable();

		pyramid->vertex.push_back(Vec3(_w, 0.0f, _l));
		pyramid->vertex.push_back(Vec3(-_w, 0.0f, _l));
		pyramid->vertex.push_back(Vec3(-_w, 0.0f, -_l));
		pyramid->vertex.push_back(Vec3(_w, 0.0f, -_l));
		
		pyramid->vertex.push_back(Vec3(0.0f, _h, 0.0f));
		pyramid->vertex.push_back(pyramid->vertex[0]);
		pyramid->vertex.push_back(pyramid->vertex[1]);

		pyramid->vertex.push_back(pyramid->vertex[4]);
		pyramid->vertex.push_back(pyramid->vertex[1]);
		pyramid->vertex.push_back(pyramid->vertex[2]);

		pyramid->vertex.push_back(pyramid->vertex[4]);
		pyramid->vertex.push_back(pyramid->vertex[2]);
		pyramid->vertex.push_back(pyramid->vertex[3]);

		pyramid->vertex.push_back(pyramid->vertex[4]);
		pyramid->vertex.push_back(pyramid->vertex[3]);
		pyramid->vertex.push_back(pyramid->vertex[0]);

		////	/* Bottom */pyramid->edge.push_back(0);	 pyramid->edge.push_back(1);	pyramid->edge.push_back(2);		pyramid->edge.push_back(3);
		////	/* Face 1 */pyramid->edge.push_back(0);	 pyramid->edge.push_back(1);	pyramid->edge.push_back(4);
		////	/* Face 2 */pyramid->edge.push_back(1);	 pyramid->edge.push_back(2);	pyramid->edge.push_back(4);
		////	/* Face 3 */pyramid->edge.push_back(2);	 pyramid->edge.push_back(3);	pyramid->edge.push_back(4);
		////	/* Face 4 */pyramid->edge.push_back(3);	 pyramid->edge.push_back(0);	pyramid->edge.push_back(4);

		for (unsigned int i = 0; i < pyramid->vertex.size(); i++)
			pyramid->edge.push_back(i);

		pyramid->face.push_back(4);

		for (int i = 1; i < 5; i++)pyramid->face.push_back(3);

		GenerateTextureMap(pyramid, _id);

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

void ModelManager::InsertModel(Renderable* _renderable, string _id)
{
	_renderable->offsetVertex = masterVectorList.size();
	models.insert(std::pair<string, Renderable *>(_id, _renderable));

	for (auto it = _renderable->vertex.begin(); it != _renderable->vertex.end(); it++)
	{
		masterVectorList.push_back(*it);
	}

	for (int i = 0; i < _renderable->edge.size(); i++)
		_renderable->edge[i] += _renderable->offsetVertex;
}

void ModelManager::GenerateTextureMap(Renderable* _renderable, string _id)
{
	for (int i = 0; i < _renderable->face.size(); i++)
	{
		if (_renderable->face[i] == 4)
		{
			_renderable->textureMap.push_back(Vec2(0, 1));
		}
		
		_renderable->textureMap.push_back(Vec2(1, 1));
		_renderable->textureMap.push_back(Vec2(1, 0));
		_renderable->textureMap.push_back(Vec2(0, 0));
	}

	for (auto it = _renderable->textureMap.begin(); it != _renderable->textureMap.end(); it++)
	{
		masterTextureCoords.push_back(*it);
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
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, it->second->width, it->second->height, 0, GL_RGB, GL_FLOAT, it->second->pixelData);
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
	textures.insert(std::pair<string, Texture*>(_id, new Texture(_pixelData, _textureWidth, _textureHeight)));
}

void ModelManager::loadTexture(string _id, string _fileName)
{
	textures.insert(std::pair<string, Texture*>(_id, new Texture(_fileName)));
}

Texture* ModelManager::getTexture(string _id)
{
	return textures.find(_id)->second;
}