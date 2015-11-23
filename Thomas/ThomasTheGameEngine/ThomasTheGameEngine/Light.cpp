#include "Light.h"
#include "ModelManager.h"
#include "OpenGLUtilities.h"
#include "LightManager.h"
#include "GameObject.h"

Light::Light(GameObject * _g, Vec4 _colourIntensity, Light_Type _type, float _radius, float _coneAngle) : Component(_g, Component::Light)
{
	colourIntensity = _colourIntensity;
	lightType = _type;
	Radius = _radius;
	ConeAngle = _coneAngle;
}

Light::~Light()
{
}

void Light::PushLight()
{
	Vec3 _forward;

	switch (lightType)
	{
		case Light_Type::Directional:
			_forward = parentObject->forward();
			LightManager::getInstance()->InputDirectionalLight(colourIntensity, Vec4(_forward.x, _forward.y, _forward.z, 0));
			break;

		case Light_Type::Point:
			LightManager::getInstance()->InputPointLight(colourIntensity, Vec4(parentObject->position.x, parentObject->position.y, parentObject->position.z, 0), Radius);
			break;

		case Light_Type::Spot:
			LightManager::getInstance()->InputSpotLight(colourIntensity, Vec4(parentObject->position.x, parentObject->position.y, parentObject->position.z, 0), Vec4(_forward.x, _forward.y, _forward.z, 0), Radius, ConeAngle);
			break;
	}	
}