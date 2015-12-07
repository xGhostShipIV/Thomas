#pragma once
#include "../Math/four_dimensions.hpp"

class Ray
{
public:
	Ray();
	Ray(Vec3, Vec3);
	~Ray();

	Vec3 point;
	Vec3 dir;
};

