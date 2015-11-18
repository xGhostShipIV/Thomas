#include "LightManager.h"
#include "ModelManager.h"

LightManager * LightManager::instance;

LightManager::LightManager()
{
	ResetDirectional();
}

LightManager::~LightManager(){}

void LightManager::ResetDirectional()
{
	directionIndex = 0;
	for (int i = 0; i < DirectionLength; i++)
	{
		Directional[i].color = Vec4::Zero();
		Directional[i].direction = Vec4::Zero();
	}
}

void LightManager::InputDirectionalLight(Vec4 _color, Vec4 _direction)
{
	if (directionIndex < DirectionLength)
	{
		Directional[directionIndex].color = _color;
		Directional[directionIndex].direction = _direction;
		directionIndex++;
	}
}

void LightManager::PushLights()
{
	//Direction
	{
		float color[DirectionLength * 4];
		float direction[DirectionLength * 4];

		for (int i = 0; i < DirectionLength; i++)
		{
			color[i * 4 + 0] = Directional[i].color.w;
			color[i * 4 + 1] = Directional[i].color.x;
			color[i * 4 + 2] = Directional[i].color.y;
			color[i * 4 + 3] = Directional[i].color.z;

			direction[i * 4 + 0] = Directional[i].direction.w;
			direction[i * 4 + 1] = Directional[i].direction.x;
			direction[i * 4 + 2] = Directional[i].direction.y;
			direction[i * 4 + 3] = Directional[i].direction.z;
		}

		glUniform4fv(ModelManager::getInstance()->lightColor_Directional_Location, DirectionLength, color);
		glUniform4fv(ModelManager::getInstance()->lightDirection_Directional_Location, DirectionLength, direction);

		ResetDirectional();
	}
		
}