#include "Renderable.h"
#include <glew.h>
#include "Transform.h"
#include "ModelManager.h"

void OpenGL_Renderable::Draw(Transform parentTransform)
{
	//Get Transform Stuff
	glUniformMatrix4fv(ModelManager::getInstance()->transformLocation, 1, GL_FALSE, parentTransform.toMat4().values);
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