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
		Spot
	};

	Light(GameObject * _g, Vec4 _colourIntensity, Light_Type _type);
	~Light();

	Light_Type type;
	Vec4 colourIntensity;

	void PushLight(Vec3 _forward);
};

