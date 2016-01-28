#pragma once
#include "../Math/four_dimensions.hpp"
#include "../Math/Plane.h"

class Ray
{
public:
	Ray();
	Ray(Vec3, Vec3);
	~Ray();

	Vec3 point;
	Vec3 dir;
	bool castTo(Plane target_, Vec3 &output_);
};

