//Author:	Mathieu Violette
//Date:		12/6/2014

#ifndef _CUBE_H_
#define _CUBE_H_

#include "GameObject.h"
#include "..\Math\four_dimensions.hpp"

class Cube : public GameObject
{
public:
	static const int NumberOfVertices = 8;

	float Length, colour;
	float vertices[NumberOfVertices][3];

	unsigned int faces[NumberOfVertices*3];

	Cube(GLint _programID, float _length = 1.0f, Vec3 _position = Vec3::Zero());
	~Cube();

	void Render() override;
	void Update(UINT32 _deltaTime) override;

protected:
	GLint program, colourLocation, rotLocation, transLocation;

	void DrawCubeOutline();
	void DrawCubeSolid();
};
#endif