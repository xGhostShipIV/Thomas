#include "Renderable.h"
#include <glew.h>
#include "GameObject.h"
#include "ModelManager.h"
#include "Texture.h"
#include "Material.h"
#include "GameProperties.h"
#include "GuiElement.h"

void OpenGL_Renderable::Draw(GameObject& parentTransform, Material * _mat, std::vector<UINT32> _textureNames)
{
	//Get textures
	std::vector<Texture*> _textures;
	for (int i = 0; i < _textureNames.size(); i++)
		_textures.push_back(ModelManager::getInstance()->getTexture(_textureNames[i]));

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

	//Not UI
	float _ui[1] = { 0 };
	glUniform1fv(ModelManager::getInstance()->UI_DRAW_Location, 1, _ui);
	float _UIdrawPercent[1] = { 1 };
	glUniform1fv(ModelManager::getInstance()->UI_DrawPercent_Location, 1, _UIdrawPercent);

	float _drawStyle[1] = { parentTransform.drawStyle };
	glUniform1fv(ModelManager::getInstance()->DrawStyle_Location, 1, _drawStyle);
	float _rRand[1] = { parentTransform.rainbowRand };
	glUniform1fv(ModelManager::getInstance()->RainbowRand_Location, 1, _rRand);

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	//Effected by light?
	float effected[3] = { isEffectedByLight.x, isEffectedByLight.y, isEffectedByLight .z};
	glUniform3fv(ModelManager::getInstance()->isEffectedByLight_Location, 1, effected);

	//Get Transform Stuff
	glUniformMatrix4fv(ModelManager::getInstance()->transformLocation, 1, GL_FALSE, parentTransform.toMat4().transpose().values);
	glUniformMatrix4fv(ModelManager::getInstance()->rotateLocation, 1, GL_FALSE, Matrix4(parentTransform.rotation).transpose().values);

	//MATERIAL UNIFORM JUNK
	float mat[] {_mat->ambient, _mat->diffuse, _mat->specular};
	glUniform3fv(ModelManager::getInstance()->materialLocation, 1, mat);

	for (int m = 0; m < meshes.size(); m++)
	{
		//Get Texture
		if (m < _textures.size() && _textures[m])
		{
			glBindTexture(GL_TEXTURE_2D, _textures[m]->address);
		}
		else if (_textures[0])
			glBindTexture(GL_TEXTURE_2D, _textures[0]->address);


		int edgeIndex = 0;

		for (int i = 0; i < meshes[m].face.size(); i++)
		{
			/*if (meshes[m].normal.size() != 0)
			{
				Vec3 _normal = Quat::rotate(parentTransform.rotation, meshes[m].normal[i]);
				float norm[] {_normal.x, _normal.y, _normal.z, 0};

				glUniform4fv(ModelManager::getInstance()->normalLocation, 1, norm);
			}*/

			//if (edgeIndex <= edge.size())
			{
				float faceNorm[] = { meshes[m].faceNormal[edgeIndex].x, meshes[m].faceNormal[edgeIndex].y, meshes[m].faceNormal[edgeIndex].z, 0 };
				glUniform4fv(ModelManager::getInstance()->faceNormalLocation, 1, faceNorm);

				if (meshes[m].face[i] == 4)
					glDrawElements(GL_QUADS, meshes[m].face[i], GL_UNSIGNED_INT, &meshes[m].edge[edgeIndex]);
				else if (meshes[m].face[i] == 3)
					glDrawElements(GL_TRIANGLES, meshes[m].face[i], GL_UNSIGNED_INT, &meshes[m].edge[edgeIndex]);

				edgeIndex += meshes[m].face[i];
			}
		}
	}

}

void OpenGL_Renderable::DrawUI(GameObject& parentTransform, Material * _mat, std::vector<UINT32> _textureNames, ScreenAnchor anchor_)
{
	//Get textures
	std::vector<Texture*> _textures;
	for (int i = 0; i < _textureNames.size(); i++)
		_textures.push_back(ModelManager::getInstance()->getTexture(_textureNames[i]));

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
	
	//IS UI
	float _ui[1] = { ((GuiElement*)&parentTransform)->drawType };
	glUniform1fv(ModelManager::getInstance()->UI_DRAW_Location, 1, _ui);
	float _UIdrawPercent[1] = { ((GuiElement*)&parentTransform)->drawPercent };
	glUniform1fv(ModelManager::getInstance()->UI_DrawPercent_Location, 1, _UIdrawPercent);

	float _drawStyle[1] = { parentTransform.drawStyle };
	glUniform1fv(ModelManager::getInstance()->DrawStyle_Location, 1, _drawStyle);
	float _rRand[1] = { parentTransform.rainbowRand };
	glUniform1fv(ModelManager::getInstance()->RainbowRand_Location, 1, _rRand);

	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);

	//Effected by light?
	float effected[3] = { isEffectedByLight.x, isEffectedByLight.y, isEffectedByLight.z };
	glUniform3fv(ModelManager::getInstance()->isEffectedByLight_Location, 1, effected);

	//Get Transform Stuff

	//Convert from screen pixels to screen percent
	Matrix4 GUITransform = parentTransform.toMat4();

	//Adjust Position based on anchor location
	switch (anchor_)
	{
		case ScreenAnchor::TOP_LEFT:
			GUITransform.values[7] += GameProperties::getInstance()->getVideoProperties()->screenHeight;
			break;
		case ScreenAnchor::TOP_CENTER:
			GUITransform.values[3] += GameProperties::getInstance()->getVideoProperties()->screenWidth / 2.0f;
			GUITransform.values[7] += GameProperties::getInstance()->getVideoProperties()->screenHeight;
			break;
		case ScreenAnchor::TOP_RIGHT:
			GUITransform.values[3] += GameProperties::getInstance()->getVideoProperties()->screenWidth;
			GUITransform.values[7] += GameProperties::getInstance()->getVideoProperties()->screenHeight;
			break;
		case ScreenAnchor::CENTER_LEFT:
			GUITransform.values[7] += GameProperties::getInstance()->getVideoProperties()->screenHeight / 2.0f;
			break;
		case ScreenAnchor::CENTER:
			GUITransform.values[3] += GameProperties::getInstance()->getVideoProperties()->screenWidth / 2.0f;
			GUITransform.values[7] += GameProperties::getInstance()->getVideoProperties()->screenHeight / 2.0f;
			break;
		case ScreenAnchor::CENTER_RIGHT:
			GUITransform.values[3] += GameProperties::getInstance()->getVideoProperties()->screenWidth;
			GUITransform.values[7] += GameProperties::getInstance()->getVideoProperties()->screenHeight / 2.0f;
			break;
		case ScreenAnchor::BOTTOM_LEFT:
			//Default, do nothing
			break;
		case ScreenAnchor::BOTTOM_CENTER:
			GUITransform.values[3] += GameProperties::getInstance()->getVideoProperties()->screenWidth / 2.0f;
			break;
		case ScreenAnchor::BOTTOM_RIGHT:
			GUITransform.values[3] += GameProperties::getInstance()->getVideoProperties()->screenWidth;
			break;
	}

	//X position
	GUITransform.values[3] = (GUITransform.values[3] / (float)GameProperties::getInstance()->getVideoProperties()->screenWidth) * 2 - 1;
	
	//Y Position
	GUITransform.values[7] = (GUITransform.values[7] / (float)GameProperties::getInstance()->getVideoProperties()->screenHeight) * 2 - 1;

	glUniformMatrix4fv(ModelManager::getInstance()->transformLocation, 1, GL_FALSE, GUITransform.transpose().values);
	glUniformMatrix4fv(ModelManager::getInstance()->rotateLocation, 1, GL_FALSE, Matrix4(parentTransform.rotation).transpose().values);

	//MATERIAL UNIFORM JUNK
	float mat[] {_mat->ambient, _mat->diffuse, _mat->specular};
	glUniform3fv(ModelManager::getInstance()->materialLocation, 1, mat);

	for (int m = 0; m < meshes.size(); m++)
	{
		//Get Texture
		if (m < _textures.size() && _textures[m])
		{
			glBindTexture(GL_TEXTURE_2D, _textures[m]->address);
		}
		else if (_textures[0])
			glBindTexture(GL_TEXTURE_2D, _textures[0]->address);


		int edgeIndex = 0;

		for (int i = 0; i < meshes[m].face.size(); i++)
		{
			if (meshes[m].normal.size() != 0)
			{
				Vec3 _normal = Quat::rotate(parentTransform.rotation, meshes[m].normal[i]);

				/*float norm[] {_normal.x, _normal.y, _normal.z, 0};
				glUniform4fv(ModelManager::getInstance()->normalLocation, 1, norm);*/
			}

			//if (edgeIndex <= edge.size())
			{
				float faceNorm[] = { meshes[m].faceNormal[edgeIndex].x, meshes[m].faceNormal[edgeIndex].y, meshes[m].faceNormal[edgeIndex].z, 0 };
				glUniform4fv(ModelManager::getInstance()->faceNormalLocation, 1, faceNorm);

				if (meshes[m].face[i] == 4)
					glDrawElements(GL_QUADS, meshes[m].face[i], GL_UNSIGNED_INT, &meshes[m].edge[edgeIndex]);
				else if (meshes[m].face[i] == 3)
					glDrawElements(GL_TRIANGLES, meshes[m].face[i], GL_UNSIGNED_INT, &meshes[m].edge[edgeIndex]);

				edgeIndex += meshes[m].face[i];
			}
		}
	}
}

void OpenGL_Renderable::DrawWireFrame(GameObject& parentTransform)
{
	//Get Transform Stuff
	glUniformMatrix4fv(ModelManager::getInstance()->transformLocation, 1, GL_FALSE, parentTransform.toMat4().transpose().values);
	glUniformMatrix4fv(ModelManager::getInstance()->rotateLocation, 1, GL_FALSE, Matrix4(parentTransform.rotation).transpose().values);

	for (int m = 0; m < meshes.size(); m++)
	{
		int edgeIndex = 0;

		for (int i = 0; i < meshes[m].face.size(); i++)
		{
			/*float norm[] {meshes[m].normal[i].x, meshes[m].normal[i].y, meshes[m].normal[i].z, 0};
			glUniform4fv(ModelManager::getInstance()->normalLocation, 1, norm);*/

			if (meshes[m].face[i] == 4)
				glDrawElements(GL_LINE_LOOP, meshes[m].face[i], GL_UNSIGNED_INT, &meshes[m].edge[edgeIndex]);
			else if (meshes[m].face[i] == 3)
				glDrawElements(GL_LINE_LOOP, meshes[m].face[i], GL_UNSIGNED_INT, &meshes[m].edge[edgeIndex]);

			edgeIndex += meshes[m].face[i];
		}
	}
}