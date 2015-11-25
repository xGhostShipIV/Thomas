#pragma once
#include "Component.h"
#include "Component.h"
#include "../Math/four_dimensions.hpp"

class Light :
	public Component
{

public:
	enum Light_Type{
		Point,
		Spot,
		Directional
	};

	//Colour is entered as (Alpha, Red, Green, Blue);
	Light(GameObject * _g, Vec4 _colourIntensity, Light_Type _type, float _coneAngle = 0.5f);

	~Light();

	Light_Type lightType;
	Vec4 colourIntensity;
	float ConeAngle;

	void PushLight();
};

