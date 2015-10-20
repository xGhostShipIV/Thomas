#include "Camera.h"
#include "GameProperties.h"
#include "dependencies\glm\glm.hpp"
#include "dependencies\glm\gtc\matrix_transform.hpp"

Camera::Camera(GLuint _shaderPosition)
{
	GameProperties * gp = GameProperties::getInstance();

	glm::mat4 m = glm::perspective(45.0f, gp->getVideoProperties()->aspectRatio, 0.1f, gp->getVideoProperties()->drawDistance);
	glm::mat4 m2 = glm::lookAt(glm::vec3(0, 0, 0), glm::vec3(0, 0, -5), glm::vec3(0, 1, 0));

	for (int i = 0; i < 16; i++)
	{
		projectionMatrix.values[i] = m[i % 4][i / 4];
		modelViewMatrix.values[i] = m2[i % 4][i / 4];
	}

	cameraMatrix = projectionMatrix * modelViewMatrix;

	shaderPosition = _shaderPosition;
}

Matrix4 Camera::getMatrix() const
{
	return cameraMatrix;
}

void Camera::Render()
{
	glUniformMatrix4fv(shaderPosition, 1, GL_FALSE, &cameraMatrix.values[0]);
}

Camera::~Camera()
{
}
