#include "Light.h"


Light::Light(GameObject * _g, Vec4 _colourIntensity, Light_Type _type) : Component(_g, Component::Light)
{
	colourIntensity = _colourIntensity;
	type = _type;
}


Light::~Light()
{
}
