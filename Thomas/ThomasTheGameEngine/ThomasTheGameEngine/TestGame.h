//Author:	Mathieu Violette
//Date:		6/6/2015(MV)
//Testbed for Game Engine

class TestGame;

#define GAMETYPE TestGame
#include "Game.h"

#ifndef TEST_GAME_H
#define TEST_GAME_H

//Lots of dirty code.... will clean up later!
///////////////////////////////////////////////
// Add to vertex shader later...
// ModelViewProjection * ((RotationMatrix * vPosition) + Translate)
///////////////////////////////////////////////
#define BUFFER_OFFSET(i) ((void*)(i))

enum VAO_IDs { Triangles, NumVAOs };
enum Buffer_IDs { ArrayBuffer, NumBuffers };
enum Attrib_IDs { vPosition = 0 };

GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];

GLint colorLocation;
float colour = 0;

const GLuint NumVertices = 6;

GLfloat vertices[NumVertices][2] = {
	{ -0.90, -0.90 }, // Triangle 1
	{ 0.85, -0.90 },
	{ -0.90, 0.85 },
	{ 0.90, -0.85 }, // Triangle 2
	{ 0.90, 0.90 },
	{ -0.85, 0.90 }
};
/////////////////////////////////////////////

class TestGame : public Game<TestGame>
{
public:
	TestGame() 
	{
		GLU::OutputOpenGLVersion();

		glGenVertexArrays(NumVAOs, VAOs);
		glBindVertexArray(VAOs[Triangles]);

		glGenBuffers(NumBuffers, Buffers);
		glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		GLuint program = GLU::UseShaders("testGame.vert", "testGame.frag");

		glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
		glEnableVertexAttribArray(vPosition);

		colorLocation = glGetUniformLocation(program, "fColor");

	}
	~TestGame(){}
protected:

	/* Game Update Code Here */
	void Update(UINT32)
	{
		colour = colour > 1000 ? 0 : colour + 1;
	}

	/* Game Render Code Here */
	void Render()
	{
		glUniform1f(colorLocation, colour);
		glDrawArrays(GL_TRIANGLES, 0, NumVertices/2);


		float input = colour + (500) > 1000 ? colour + (500) - 1000 : colour + (500);
		glUniform1f(colorLocation, input);
		glDrawArrays(GL_TRIANGLES, NumVertices / 2, NumVertices / 2);

		glBindVertexArray(VAOs[Triangles]);	//It is already defined in init() above
		
	}
};

#endif