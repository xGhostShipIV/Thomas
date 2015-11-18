#include "Light.h"
#include "ModelManager.h"
#include "OpenGLUtilities.h"
#include "LightManager.h"

Light::Light(GameObject * _g, Vec4 _colourIntensity, Light_Type _type) : Component(_g, Component::Light)
{
	colourIntensity = _colourIntensity;
	lightType = _type;
}

Light::~Light()
{
}

void Light::PushLight(Vec3 _forward)
{
	switch (lightType)
	{
		case Light_Type::Directional:
			LightManager::getInstance()->InputDirectionalLight(colourIntensity, Vec4(_forward.x, _forward.y, _forward.z, 0));
			break;
	}	
}