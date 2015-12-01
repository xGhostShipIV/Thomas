#include "Renderable.h"
#include <glew.h>
#include "GameObject.h"
#include "ModelManager.h"
#include "Texture.h"
#include "Material.h"

void OpenGL_Renderable::Draw(GameObject& parentTransform, Material * _mat, Texture *_texture)
{

	//Switch Face Culling Mode
	switch (drawMode)
	{
		case ModelManager::Draw_Mode::CCW:
			glFrontFace(GL_CCW);
			break;
		case ModelManager::Draw_Mode::CW:
			glFrontFace(GL_CW);
			break;
	}

	//Get Transform Stuff
	glUniformMatrix4fv(ModelManager::getInstance()->transformLocation, 1, GL_FALSE, parentTransform.toMat4().transpose().values);
	float pos[] {parentTransform.position.x, parentTransform.position.y, parentTransform.position.z, 0};
	glUniform4fv(ModelManager::getInstance()->translateLocation, 1, pos);

	//MATERIAL UNIFORM JUNK
	float mat[] {_mat->ambient, _mat->diffuse, _mat->specular};
	glUniform3fv(ModelManager::getInstance()->materialLocation, 1, mat);

	//Get Texture
	if (_texture)
	{
		glBindTexture(GL_TEXTURE_2D, _texture->address);
	}
	// else set texture to null??

	int edgeIndex = 0;

	for (int i = 0; i < face.size(); i++)
	{
		if (normal.size() != 0)
		{
			Vec3 _normal = Quat::rotate(parentTransform.rotation, normal[i]);

			float norm[] {_normal.x, _normal.y, _normal.z, 0};
			glUniform4fv(ModelManager::getInstance()->normalLocation, 1, norm);
		}

		//if (edgeIndex <= edge.size())
		{
			if (face[i] == 4)
				glDrawElements(GL_QUADS, face[i], GL_UNSIGNED_INT, &edge[edgeIndex]);
			else if (face[i] == 3)
				glDrawElements(GL_TRIANGLES, face[i], GL_UNSIGNED_INT, &edge[edgeIndex]);

			edgeIndex += face[i];
		}
	}
}

void OpenGL_Renderable::DrawWireFrame(GameObject& parentTransform)
{
	//Get Transform Stuff
	glUniformMatrix4fv(ModelManager::getInstance()->transformLocation, 1, GL_FALSE, parentTransform.toMat4().transpose().values);

	float pos[] {parentTransform.position.x, parentTransform.position.y, parentTransform.position.z, 0};
	glUniform4fv(ModelManager::getInstance()->translateLocation, 1, pos);

	int edgeIndex = 0;

	for (int i = 0; i < face.size(); i++)
	{
		float norm[] {normal[i].x, normal[i].y, normal[i].z, 0};
		glUniform4fv(ModelManager::getInstance()->normalLocation, 1, norm);

		if (face[i] == 4)
			glDrawElements(GL_LINE_LOOP, face[i], GL_UNSIGNED_INT, &edge[edgeIndex]);
		else if (face[i] == 3)
			glDrawElements(GL_LINE_LOOP, face[i], GL_UNSIGNED_INT, &edge[edgeIndex]);

		edgeIndex += face[i];
	}
}