//Author:	Mathieu Violette
//Date:		5/26/2015(MV)

#include "GameManager.h"
//#include <SDL.h>

GameManager* GameManager::instance = nullptr;

//Declare Update function
//void Update(int ID);


/* Returns the instance of GameManager */
GameManager* GameManager::GetInstance()
{
	if (instance == nullptr)
		instance = new GameManager();
	
	return instance;
}

/* Inits GLUT Window*/
GameManager::GameManager()
{
	updateFunc = nullptr;
	renderFunc = nullptr;

	//GLUT stuff
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(1024, 768);
	glutInitWindowPosition(825, 100);
	glutCreateWindow("Tutorial 01");

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);


	///SDL stuff
	//SDL_Init(SDL_INIT_EVERYTHING);
}

GameManager::~GameManager()
{
	//SDL_Quit();
}

//Wrapper Classes for OpenGL linking
void RenderSceneWrapper()
{
	GameManager::GetInstance()->RenderScene();
}
void UpdateWrapper(int ID)
{
	GameManager::GetInstance()->Update(ID);
}

/* Called to start game. Links glut Functions. */
void GameManager::StartProgram(void render(void), UpdateFunc update)
{
	updateFunc = update;
	renderFunc = render;

	//glutReshapeFunc(ChangeSize);
	glutDisplayFunc(RenderSceneWrapper);
	glutTimerFunc(16, UpdateWrapper, 1);
	
	glutMainLoop();
}

/* Performs engine draw calls, then calls game's render function */
void GameManager::RenderScene() /* Engine's Render*/
{
	glClear(GL_COLOR_BUFFER_BIT);
	glutSwapBuffers();

	//Game's Render Call
	if (renderFunc != nullptr)
		renderFunc();
}

/* Performs event Handling, then calls game's update function */
void GameManager::Update(int ID) /* Engine's Update*/
{
	//Event Handling


	//Game's Update Call
	if (updateFunc != nullptr)
		updateFunc(ID);
}