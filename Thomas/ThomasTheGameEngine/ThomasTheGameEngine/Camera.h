#pragma once
#include "GameObject.h"
#include "../Math/four_dimensions.hpp"

class Camera :
	public GameObject
{
public:
	Camera();
	~Camera();

	Matrix4 getMatrix() const;
	void CalculateCameraMatrix();
	void Render() override;
	void Update(UINT32 _deltaTime) override;

private:
	GLuint shaderPosition;

	Matrix4 projectionMatrix;
	Matrix4 modelViewMatrix;
	Matrix4 cameraMatrix;
};

