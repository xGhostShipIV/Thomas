//Author:	Mathieu Violette
//Date:		5/26/2015(MV)

#include "GameManager.h"

GameManager* GameManager::instance = nullptr;

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
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(1024, 768);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Tutorial 01");

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

GameManager::~GameManager()
{

}

/* Called to start game. Links glut Functions. */
void GameManager::StartProgram(void render(void))
{
	glutDisplayFunc(render);

	

	glutMainLoop();
}