#pragma once
#include "GameObject.h"
#include "../Math/four_dimensions.hpp"

class Camera :
	public GameObject
{
public:
	Camera(GLuint _shaderPosition);
	~Camera();

	Matrix4 getMatrix() const;

	void Render() override;

private:
	GLuint shaderPosition;

	Matrix4 projectionMatrix;
	Matrix4 modelViewMatrix;
	Matrix4 cameraMatrix;
};

