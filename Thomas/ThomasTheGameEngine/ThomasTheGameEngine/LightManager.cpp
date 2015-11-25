#include "LightManager.h"
#include "ModelManager.h"

LightManager * LightManager::instance;

LightManager::LightManager()
{
	ResetDirectional();
	ResetPoint();
	ResetSpot();
}

LightManager::~LightManager(){}

void LightManager::ResetDirectional()
{
	directionalIndex = 0;
	for (int i = 0; i < DirectionalLength; i++)
	{
		Directional[i].color = Vec4::Zero();
		Directional[i].direction = Vec4::Zero();
	}
}

void LightManager::ResetPoint()
{
	pointIndex = 0;
	for (int i = 0; i < PointLength; i++)
	{
		Point[i].color = Vec4::Zero();
		Point[i].position = Vec4::Zero();
	}
}

void LightManager::ResetSpot()
{
	spotIndex = 0;
	for (int i = 0; i < SpotLength; i++)
	{
		Spot[i].color = Vec4::Zero();
		Spot[i].position = Vec4::Zero();
		Spot[i].direction = Vec4::Zero();
		Spot[i].coneAngle = 0;
	}
}

void LightManager::InputDirectionalLight(Vec4 _color, Vec4 _direction)
{
	if (directionalIndex < DirectionalLength)
	{
		Directional[directionalIndex].color = _color;
		Directional[directionalIndex].direction = _direction;
		directionalIndex++;
	}
}

void LightManager::InputPointLight(Vec4 _color, Vec4 _position)
{
	if (pointIndex < PointLength)
	{
		Point[pointIndex].color = _color;
		Point[pointIndex].position = _position;
		pointIndex++;
	}
}

void LightManager::InputSpotLight(Vec4 _color, Vec4 _position, Vec4 _direction, float _coneAngle)
{
	if (spotIndex < SpotLength)
	{
		Spot[spotIndex].color = _color;
		Spot[spotIndex].position = _position;
		Spot[spotIndex].direction = _direction;
		Spot[spotIndex].coneAngle = _coneAngle;
		spotIndex++;
	}
}

void LightManager::PushLights()
{
	//Direction
	{
		float color[DirectionalLength * 4];
		float direction[DirectionalLength * 4];

		for (int i = 0; i < DirectionalLength; i++)
		{
			color[i * 4 + 0] = Directional[i].color.x;
			color[i * 4 + 1] = Directional[i].color.y;
			color[i * 4 + 2] = Directional[i].color.z;
			color[i * 4 + 3] = Directional[i].color.w;

			direction[i * 4 + 0] = Directional[i].direction.x;
			direction[i * 4 + 1] = Directional[i].direction.y;
			direction[i * 4 + 2] = Directional[i].direction.z;
			direction[i * 4 + 3] = Directional[i].direction.w;
		}

		glUniform4fv(ModelManager::getInstance()->lightColor_Directional_Location, DirectionalLength, color);
		glUniform4fv(ModelManager::getInstance()->lightDirection_Directional_Location, DirectionalLength, direction);

		ResetDirectional();
	}

	//Point
	{
		float color[PointLength * 4];
		float position[PointLength * 4];

		for (int i = 0; i < PointLength; i++)
		{
			color[i * 4 + 0] = Point[i].color.x;
			color[i * 4 + 1] = Point[i].color.y;
			color[i * 4 + 2] = Point[i].color.z;
			color[i * 4 + 3] = Point[i].color.w;

			position[i * 4 + 0] = Point[i].position.x;
			position[i * 4 + 1] = Point[i].position.y;
			position[i * 4 + 2] = Point[i].position.z;
			position[i * 4 + 3] = Point[i].position.w;
		}

		glUniform4fv(ModelManager::getInstance()->lightColor_Point_Location, PointLength, color);
		glUniform4fv(ModelManager::getInstance()->lightPosition_Point_Location, PointLength, position);

		ResetPoint();
	}

	//Spot
	{
		float color[SpotLength * 4];
		float position[SpotLength * 4];
		float direction[SpotLength * 4];
		float angle[SpotLength];

		for (int i = 0; i < SpotLength; i++)
		{
			color[i * 4 + 0] = Spot[i].color.x;
			color[i * 4 + 1] = Spot[i].color.y;
			color[i * 4 + 2] = Spot[i].color.z;
			color[i * 4 + 3] = Spot[i].color.w;

			position[i * 4 + 0] = Spot[i].position.x;
			position[i * 4 + 1] = Spot[i].position.y;
			position[i * 4 + 2] = Spot[i].position.z;
			position[i * 4 + 3] = Spot[i].position.w;

			direction[i * 4 + 0] = Spot[i].direction.x;
			direction[i * 4 + 1] = Spot[i].direction.y;
			direction[i * 4 + 2] = Spot[i].direction.z;
			direction[i * 4 + 3] = Spot[i].direction.w;

			angle[i] = Spot[i].coneAngle;
		}

		glUniform4fv(ModelManager::getInstance()->lightColor_Spot_Location, SpotLength, color);
		glUniform4fv(ModelManager::getInstance()->lightPosition_Spot_Location, SpotLength, position);
		glUniform4fv(ModelManager::getInstance()->lightDirection_Spot_Location, SpotLength, direction);
		glUniform1fv(ModelManager::getInstance()->lightAngle_Spot_Location, SpotLength, angle);

		ResetSpot();
	}
}