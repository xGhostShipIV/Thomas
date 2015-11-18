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

	Light(GameObject * _g, Vec4 _colourIntensity, Light_Type _type);
	~Light();

	Light_Type lightType;
	Vec4 colourIntensity;

	void PushLight(Vec3 _forward);
};

