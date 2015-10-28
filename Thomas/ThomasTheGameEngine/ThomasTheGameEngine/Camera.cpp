#include "Camera.h"
#include "GameProperties.h"
#include "dependencies\glm\glm.hpp"
#include "dependencies\glm\gtc\matrix_transform.hpp"
#include "dependencies\glm\gtc\type_ptr.hpp"

#include <iostream>

Camera::Camera(GLuint _shaderPosition) : GameObject(Vec3(0, 0, -2))
{
	CalculateCameraMatrix();	
	shaderPosition = _shaderPosition;
}

void Camera::CalculateCameraMatrix()
{
	GameProperties * gp = GameProperties::getInstance();

	glm::mat4 m = glm::perspective(45.0f, gp->getVideoProperties()->aspectRatio, 0.00001f, gp->getVideoProperties()->drawDistance);

	Vec4 camForward = (Matrix4::Rotate(transform->rotation) * Vec4::BasisZ());
	Vec3 forawrd = transform->position + Vec3(camForward.x, camForward.y, camForward.z);

	glm::mat4 m2 = glm::lookAt(glm::vec3(transform->position.x, transform->position.y, transform->position.z), glm::vec3(forawrd.x, forawrd.y, forawrd.z), glm::vec3(0, 1, 0));
	
	//Get array pointer to glm matrix
	const float *mSource = (const float*)glm::value_ptr(m);
	const float *m2Source = (const float*)glm::value_ptr(m2);

	for (int i = 0; i < 16; i++)
	{
		projectionMatrix.values[i] = mSource[i];
		modelViewMatrix.values[i] = m2Source[i];
	}
	
	//Note: To get the same results as GLM we must transpose both before AND after multiplication.	
	projectionMatrix = projectionMatrix.transpose();
	modelViewMatrix = modelViewMatrix.transpose();
	
	cameraMatrix = projectionMatrix * modelViewMatrix;
	cameraMatrix = cameraMatrix.transpose();
}

Matrix4 Camera::getMatrix() const
{
	return cameraMatrix;
}

void Camera::Update(UINT32 _deltaTime)
{
	CalculateCameraMatrix();
	glUniformMatrix4fv(shaderPosition, 1, GL_FALSE, cameraMatrix.values);
}

void Camera::Render()
{		
}

Camera::~Camera()
{
}
