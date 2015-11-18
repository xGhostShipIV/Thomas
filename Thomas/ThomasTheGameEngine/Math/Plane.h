#pragma once
#include "four_dimensions.hpp"

class Plane
{
public:
	Vec3 normal;
	float D;

	Plane(Vec3 _normal, float _d);
	Plane(Vec3 _Pa, Vec3 _Pb, Vec3 _Pc);
	~Plane();

	Vec4 getPlane();
	Vec3 getNormal();
	float getDistance();

	float DistanceToPoint(Vec3 _point);
};

