#include "Plane.h"


Plane::Plane(Vec3 _normal, float _d)
{
	normal = _normal;
	D = _d;
}

Plane::Plane(Vec3 _Pa, Vec3 _Pb, Vec3 _Pc)
{
	normal = Vec3::cross((_Pb - _Pa), (_Pc - _Pa));
	D = -Vec3::dot(normal, _Pa);
}

Plane::~Plane()
{
}

float Plane::DistanceToPoint(Vec3 _point)
{
	return (Vec3::dot(normal, _point) + D);
}

Vec4 Plane::getPlane()
{
	return Vec4(D, normal.x, normal.y, normal.z);
}

Vec3 Plane::getNormal()
{
	return normal;
}

float Plane::getDistance()
{
	return D;
}