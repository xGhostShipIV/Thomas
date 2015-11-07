#pragma once
#include "GameObject.h"
#include "../Math/four_dimensions.hpp"

class Camera :
	public GameObject
{
public:
	Camera();
	~Camera();

	//Returns a matrix of all aspects of the camera to be used by the GPU.
	// I.e. projection and model view matrix
	Matrix4 getMatrix() const;

	//Recalculates the above matrix
	void CalculateCameraMatrix();

	//Overridden methods inherited from the base class
	void Render() override;
	void Update(UINT32 _deltaTime) override;

private:
	//OpenGL specific identifier
	GLuint cameraMatrixLocation, cameraPositionLocation;

	//All matricies associated with the camera
	Matrix4 projectionMatrix;
	Matrix4 modelViewMatrix;
	Matrix4 cameraMatrix;
};

