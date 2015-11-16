#include "Light.h"
#include "ModelManager.h"
#include "OpenGLUtilities.h"

Light::Light(GameObject * _g, Vec4 _colourIntensity, Light_Type _type) : Component(_g, Component::Light)
{
	colourIntensity = _colourIntensity;
	type = _type;
}


Light::~Light()
{
}

void Light::PushLight(Vec3 _forward)
{
	float light[] {colourIntensity.x, colourIntensity.y, colourIntensity.z, colourIntensity.w};
	glUniform4fv(ModelManager::getInstance()->lightColorLocation, 1, light);

	float direction[] {_forward.x, _forward.y, _forward.z, 0};
	glUniform4fv(ModelManager::getInstance()->lightDirectionLocation, 1, direction);
}