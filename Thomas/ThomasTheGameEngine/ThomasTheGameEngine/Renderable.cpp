#include "Renderable.h"
#include <glew.h>
#include "GameObject.h"
#include "ModelManager.h"
#include "Texture.h"

void OpenGL_Renderable::Draw(GameObject& parentTransform, Texture *_texture)
{
	//Get Transform Stuff
	glUniformMatrix4fv(ModelManager::getInstance()->transformLocation, 1, GL_FALSE, parentTransform.toMat4().transpose().values);

	//Get Texture
	if (_texture)
	{
		glBindTexture(GL_TEXTURE_2D, _texture->address);
		glUniform1f(ModelManager::getInstance()->colourLocation, -2);
	}
	else
		glUniform1f(ModelManager::getInstance()->colourLocation, 500);

	int edgeIndex = 0;

	for (int i = 0; i < face.size(); i++)
	{
		if (face[i] == 4)
			glDrawElements(GL_QUADS, face[i], GL_UNSIGNED_INT, &edge[edgeIndex]);
		else if (face[i] == 3)
			glDrawElements(GL_TRIANGLES, face[i], GL_UNSIGNED_INT, &edge[edgeIndex]);

		edgeIndex += face[i];
	}		
}

void OpenGL_Renderable::DrawWireFrame(GameObject& parentTransform)
{
	//Get Transform Stuff
	glUniformMatrix4fv(ModelManager::getInstance()->transformLocation, 1, GL_FALSE, parentTransform.toMat4().transpose().values);
	glUniform1f(ModelManager::getInstance()->colourLocation, -1);

	int edgeIndex = 0;

	for (int i = 0; i < face.size(); i++)
	{
		if (face[i] == 4)
			glDrawElements(GL_LINE_LOOP, face[i], GL_UNSIGNED_INT, &edge[edgeIndex]);
		else if (face[i] == 3)
			glDrawElements(GL_LINE_LOOP, face[i], GL_UNSIGNED_INT, &edge[edgeIndex]);

		edgeIndex += face[i];
	}
}