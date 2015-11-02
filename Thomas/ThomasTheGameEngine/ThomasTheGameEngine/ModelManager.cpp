#include "ModelManager.h"
#include "Renderable.h"
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

		/* Face 1 */	cube->edge.push_back(0);	cube->edge.push_back(1);	cube->edge.push_back(2);	cube->edge.push_back(3);
		/* Face 2 */	cube->edge.push_back(4);	cube->edge.push_back(5);	cube->edge.push_back(6);	cube->edge.push_back(7);
		/* Face 3 */	cube->edge.push_back(0);	cube->edge.push_back(3);	cube->edge.push_back(7);	cube->edge.push_back(4);
		/* Face 4 */	cube->edge.push_back(1);	cube->edge.push_back(2);	cube->edge.push_back(6);	cube->edge.push_back(5);
		/* Face 5 */	cube->edge.push_back(0);	cube->edge.push_back(1);	cube->edge.push_back(5);	cube->edge.push_back(4);
		/* Face 6 */	cube->edge.push_back(3);	cube->edge.push_back(2);	cube->edge.push_back(6);	cube->edge.push_back(7);


		for (int i = 0; i < 6; i++)
			cube->face.push_back(4);

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


		/* Bottom */pyramid->edge.push_back(0);	 pyramid->edge.push_back(1);	pyramid->edge.push_back(2);		pyramid->edge.push_back(3);
		/* Face 1 */pyramid->edge.push_back(0);	 pyramid->edge.push_back(1);	pyramid->edge.push_back(4);
		/* Face 2 */pyramid->edge.push_back(1);	 pyramid->edge.push_back(2);	pyramid->edge.push_back(4);
		/* Face 3 */pyramid->edge.push_back(2);	 pyramid->edge.push_back(3);	pyramid->edge.push_back(4);
		/* Face 4 */pyramid->edge.push_back(3);	 pyramid->edge.push_back(0);	pyramid->edge.push_back(4);

		pyramid->face.push_back(4);

		for (int i = 1; i < 5; i++)pyramid->face.push_back(3);

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


#define BUFFER_OFFSET(i) ((void*)(i))
void ModelManager::PushModels()
{
	//Push vertex to GPU
	glGenVertexArrays(1, VAOs);
	glBindVertexArray(VAOs[0]);

	glGenBuffers(1, Buffers);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[0]);

	int arraySize = masterVectorList.size() * 3 * 4;
	float * newMasterList = new float[masterVectorList.size() * 3];

	//populate
	for (int i = 0; i < masterVectorList.size(); i++)
	{
		//newMasterList[i] = new float[3];


		newMasterList[i * 3] = masterVectorList[i].x;
		newMasterList[3 * i + 1] = masterVectorList[i].y;
		newMasterList[3 * i + 2] = masterVectorList[i].z;
	}

	//std::cout << "\n" << arraySize << "\n";

	glBufferData(GL_ARRAY_BUFFER, arraySize, newMasterList, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(0);

	/*float * data = new float[masterVectorList.size() * 3];

	for (int i = 0; i < masterVectorList.size() * 3; i++)
	{
	data[i] = 8;
	}

	glGetBufferSubData(GL_ARRAY_BUFFER, 0, arraySize, &data[0]);*/

	/*for (int i = 0; i < masterVectorList.size() * 3; i++)
		std::cout << std::endl << newMasterList[i];

		std::cout << std::endl << std::endl;*/

	/*for (int i = 0; i < masterVectorList.size() * 3; i++)
		std::cout << std::endl << data[i];*/


	//for (int i = 0; i < masterVectorList.size(); i++)
	//{
	//	delete[] newMasterList[i];
	//}
	delete newMasterList;
	//delete data;
}