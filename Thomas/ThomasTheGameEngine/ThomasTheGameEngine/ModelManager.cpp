#include "ModelManager.h"
#include "Renderable.h"
#include "Texture.h"
#include "OpenGLUtilities.h"

ModelManager * ModelManager::instance;
GLuint ModelManager::transformLocation;
GLuint ModelManager::translateLocation;
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


ModelManager::ModelManager(Render_Mode _render_mode)
{
	render_mode = _render_mode;

	if (_render_mode == RENDER_MODE_OPENGL)
	{
		program = GLU::UseShaders("testGame.vert", "testGame.frag");

		transformLocation = glGetUniformLocation(program, "Transform");
		translateLocation = glGetUniformLocation(program, "vTranslate");
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

void ModelManager::CreateCuboid(string _id, float _w, float _h, float _l)
{
	Renderable * cube;

	switch (render_mode)
	{
	case ModelManager::Render_OpenGL:

		cube = new OpenGL_Renderable();

		/* Face Back */
		cube->vertex.push_back(Vec3(-_w, _h, _l));
		cube->vertex.push_back(Vec3(_w, _h, _l));
		cube->vertex.push_back(Vec3(_w, -_h, _l));
		cube->vertex.push_back(Vec3(-_w, -_h, _l));

		/* Face Front */
		cube->vertex.push_back(Vec3(-_w, -_h, -_l));
		cube->vertex.push_back(Vec3(_w, -_h, -_l));
		cube->vertex.push_back(Vec3(_w, _h, -_l));
		cube->vertex.push_back(Vec3(-_w, _h, -_l));
		/* Face Left */
		cube->vertex.push_back(cube->vertex[0]);
		cube->vertex.push_back(cube->vertex[3]);
		cube->vertex.push_back(cube->vertex[4]);
		cube->vertex.push_back(cube->vertex[7]);
		/* Face Right */
		cube->vertex.push_back(cube->vertex[6]);
		cube->vertex.push_back(cube->vertex[5]);
		cube->vertex.push_back(cube->vertex[2]);
		cube->vertex.push_back(cube->vertex[1]);
		/* Face Top */
		cube->vertex.push_back(cube->vertex[7]);
		cube->vertex.push_back(cube->vertex[6]);
		cube->vertex.push_back(cube->vertex[1]);
		cube->vertex.push_back(cube->vertex[0]);
		/* Face Bottom */
		cube->vertex.push_back(cube->vertex[3]);
		cube->vertex.push_back(cube->vertex[2]);
		cube->vertex.push_back(cube->vertex[5]);
		cube->vertex.push_back(cube->vertex[4]);
		
		
		///* Face Back */		cube->edge.push_back(0);	cube->edge.push_back(1);	cube->edge.push_back(2);	cube->edge.push_back(3);
		///* Face Front */		cube->edge.push_back(4);	cube->edge.push_back(5);	cube->edge.push_back(6);	cube->edge.push_back(7);
		///* Face Left */		cube->edge.push_back(0);	cube->edge.push_back(3);	cube->edge.push_back(4);	cube->edge.push_back(7);
		///* Face Right */		cube->edge.push_back(6);	cube->edge.push_back(5);	cube->edge.push_back(2);	cube->edge.push_back(1);
		///* Face Top */		cube->edge.push_back(7);	cube->edge.push_back(6);	cube->edge.push_back(1);	cube->edge.push_back(0);
		///* Face Bottom */		cube->edge.push_back(3);	cube->edge.push_back(2);	cube->edge.push_back(5);	cube->edge.push_back(4);

		for (unsigned int i = 0; i < cube->vertex.size(); i++)
			cube->edge.push_back(i);

		for (int i = 0; i < 6; i++)
			cube->face.push_back(4);

		GenerateNormals(cube);
		GenerateTextureMap(cube);

		InsertModel(cube, _id);

		break;
	case ModelManager::Render_DirectX:
		break;
	case ModelManager::Render_Ogre:
		break;
	}
}

void ModelManager::CreateSkybox(string _id, float _size)
{
	Renderable * skybox;

	switch (render_mode)
	{
	case ModelManager::Render_OpenGL:

		skybox = new OpenGL_Renderable();

		/* Face Front */
		skybox->vertex.push_back(Vec3(-_size, -_size, _size)); //3
		skybox->vertex.push_back(Vec3(_size, -_size, _size)); //2
		skybox->vertex.push_back(Vec3(_size, _size, _size)); //1
		skybox->vertex.push_back(Vec3(-_size, _size, _size)); //0

		/* Face Back */
		skybox->vertex.push_back(Vec3(-_size, _size, -_size)); //7
		skybox->vertex.push_back(Vec3(_size, _size, -_size)); //6
		skybox->vertex.push_back(Vec3(_size, -_size, -_size)); //5
		skybox->vertex.push_back(Vec3(-_size, -_size, -_size)); //4
		/* Face Left */
		skybox->vertex.push_back(skybox->vertex[0]);
		skybox->vertex.push_back(skybox->vertex[3]);
		skybox->vertex.push_back(skybox->vertex[4]);
		skybox->vertex.push_back(skybox->vertex[7]);
		/* Face Right */
		skybox->vertex.push_back(skybox->vertex[6]);
		skybox->vertex.push_back(skybox->vertex[5]);
		skybox->vertex.push_back(skybox->vertex[2]);
		skybox->vertex.push_back(skybox->vertex[1]);
		/* Face Top */
		skybox->vertex.push_back(skybox->vertex[7]);
		skybox->vertex.push_back(skybox->vertex[6]);
		skybox->vertex.push_back(skybox->vertex[1]);
		skybox->vertex.push_back(skybox->vertex[0]);
		/* Face Bottom */
		skybox->vertex.push_back(skybox->vertex[3]);
		skybox->vertex.push_back(skybox->vertex[2]);
		skybox->vertex.push_back(skybox->vertex[5]);
		skybox->vertex.push_back(skybox->vertex[4]);

		for (unsigned int i = 0; i < skybox->vertex.size(); i++)
			skybox->edge.push_back(i);

		for (int i = 0; i < 6; i++)
			skybox->face.push_back(4);

		GenerateNormals(skybox);

		//Generate Cubemap 
		{
			//Front
			skybox->textureMap.push_back(Vec2(1, 2/3.0f));
			skybox->textureMap.push_back(Vec2(0.75f, 2/3.0f));
			skybox->textureMap.push_back(Vec2(0.75f, 1/3.0f));
			skybox->textureMap.push_back(Vec2(1, 1/3.0f));

			//Back
			skybox->textureMap.push_back(Vec2(0.25f, 1/3.0f));
			skybox->textureMap.push_back(Vec2(0.5f, 1/3.0f));
			skybox->textureMap.push_back(Vec2(0.5f, 2/3.0f));
			skybox->textureMap.push_back(Vec2(0.25f, 2/3.0f));

			//Left  !
			skybox->textureMap.push_back(Vec2(0, 2/3.0f));
			skybox->textureMap.push_back(Vec2(0, 1/3.0f));
			skybox->textureMap.push_back(Vec2(0.25f, 1/3.0f));
			skybox->textureMap.push_back(Vec2(0.25f, 2/3.0f));

			//Right  !
			skybox->textureMap.push_back(Vec2(0.50f, 2/3.0f));
			skybox->textureMap.push_back(Vec2(0.50f, 1/3.0f));
			skybox->textureMap.push_back(Vec2(0.75f, 1/3.0f));
			skybox->textureMap.push_back(Vec2(0.75f, 2/3.0f));

			//Bottom  ?
			skybox->textureMap.push_back(Vec2(0.25f, 2/3.0f));
			skybox->textureMap.push_back(Vec2(0.50f, 2/3.0f));
			skybox->textureMap.push_back(Vec2(0.50f, 1));
			skybox->textureMap.push_back(Vec2(0.25f, 1));

			//Top  ?
			skybox->textureMap.push_back(Vec2(0.25f, 0));
			skybox->textureMap.push_back(Vec2(0.50f, 0));
			skybox->textureMap.push_back(Vec2(0.50f, 1/3.0f));
			skybox->textureMap.push_back(Vec2(0.25f, 1/3.0f));
		}

		for (auto it = skybox->textureMap.begin(); it != skybox->textureMap.end(); it++)
		{
			masterTextureCoords.push_back(*it);
		}

		InsertModel(skybox, _id);

		break;
	case ModelManager::Render_DirectX:
		break;
	case ModelManager::Render_Ogre:
		break;
	}
}

void ModelManager::CreatePyramid(string _id, float _w, float _h, float _l)
{
	Renderable * pyramid;

	switch (render_mode)
	{
	case ModelManager::Render_OpenGL:

		pyramid = new OpenGL_Renderable();

		pyramid->vertex.push_back(Vec3(_w, 0.0f, -_l));
		pyramid->vertex.push_back(Vec3(-_w, 0.0f, -_l));
		pyramid->vertex.push_back(Vec3(-_w, 0.0f, _l));
		pyramid->vertex.push_back(Vec3(_w, 0.0f, _l));
		
		pyramid->vertex.push_back(Vec3(0.0f, _h, 0.0f));
		pyramid->vertex.push_back(pyramid->vertex[3]);
		pyramid->vertex.push_back(pyramid->vertex[2]);

		pyramid->vertex.push_back(pyramid->vertex[4]);
		pyramid->vertex.push_back(pyramid->vertex[2]);
		pyramid->vertex.push_back(pyramid->vertex[1]);

		pyramid->vertex.push_back(pyramid->vertex[4]);
		pyramid->vertex.push_back(pyramid->vertex[1]);
		pyramid->vertex.push_back(pyramid->vertex[0]);

		pyramid->vertex.push_back(pyramid->vertex[4]);
		pyramid->vertex.push_back(pyramid->vertex[0]);
		pyramid->vertex.push_back(pyramid->vertex[3]);

		////	/* Bottom */pyramid->edge.push_back(0);	 pyramid->edge.push_back(1);	pyramid->edge.push_back(2);		pyramid->edge.push_back(3);
		////	/* Face 1 */pyramid->edge.push_back(0);	 pyramid->edge.push_back(1);	pyramid->edge.push_back(4);
		////	/* Face 2 */pyramid->edge.push_back(1);	 pyramid->edge.push_back(2);	pyramid->edge.push_back(4);
		////	/* Face 3 */pyramid->edge.push_back(2);	 pyramid->edge.push_back(3);	pyramid->edge.push_back(4);
		////	/* Face 4 */pyramid->edge.push_back(3);	 pyramid->edge.push_back(0);	pyramid->edge.push_back(4);

		for (unsigned int i = 0; i < pyramid->vertex.size(); i++)
			pyramid->edge.push_back(i);

		pyramid->face.push_back(4);

		for (int i = 1; i < 5; i++)pyramid->face.push_back(3);

		GenerateNormals(pyramid);
		GenerateTextureMap(pyramid);

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

	switch (render_mode)
	{
	case ModelManager::Render_OpenGL:

		plane = new OpenGL_Renderable();

		_h /= 2.0f;
		_w /= 2.0f;

		plane->vertex.push_back(Vec3(-_w, _h, 0.0f));
		plane->vertex.push_back(Vec3(_w, _h, 0.0f));
		plane->vertex.push_back(Vec3(_w, -_h, 0.0f));
		plane->vertex.push_back(Vec3(-_w, -_h, 0.0f));

		for (unsigned int i = 0; i < plane->vertex.size(); i++)
			plane->edge.push_back(i);

		for (int i = 0; i < 1; i++)
			plane->face.push_back(4);

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

void ModelManager::GenerateTextureMap(Renderable* _renderable, float _uvRepeatX, float _uvRepeatY)
{
	for (int i = 0; i < _renderable->face.size(); i++)
	{
		if (_renderable->face[i] == 4)
		{
			_renderable->textureMap.push_back(Vec2(0, _uvRepeatY));
		}
		
		_renderable->textureMap.push_back(Vec2(_uvRepeatX, _uvRepeatY));
		_renderable->textureMap.push_back(Vec2(_uvRepeatX, 0));
		_renderable->textureMap.push_back(Vec2(0, 0));
	}

	for (auto it = _renderable->textureMap.begin(); it != _renderable->textureMap.end(); it++)
	{
		masterTextureCoords.push_back(*it);
	}
}

void ModelManager::GenerateNormals(Renderable* _renderable)
{
	int offset = 0;

	for (int i = 0; i < _renderable->face.size(); i++)
	{
		Vec3 p1 = _renderable->vertex[_renderable->edge[offset]];
		Vec3 p2 = _renderable->vertex[_renderable->edge[offset + 1]];
		Vec3 p3 = _renderable->vertex[_renderable->edge[offset + 2]];

		Vec3 A = p1 - p2;
		Vec3 B = p2 - p3;

		Vec3 normal = Vec3::cross(A, B).Normalized();

		float dotP = Vec3::dot(p1, normal);

		if (Vec3::dot(p1, normal) > 0)
			normal *= -1;

		_renderable->normal.push_back(normal);

		offset += _renderable->face[i];
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

	SDL_FreeSurface(texture);
	
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
	texture = IMG_Load(_fileName.c_str());

	if (texture == NULL)		{
		printf("Image failed to load! SDL_image Error: %s\n", IMG_GetError());
		return;
	}

	Texture * t = new Texture(texture);
	textures.insert(std::pair<string, Texture*>(_id, t));
}

Texture* ModelManager::getTexture(string _id)
{
	return textures.find(_id)->second;
}