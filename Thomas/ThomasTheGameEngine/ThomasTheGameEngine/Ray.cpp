#include "Ray.h"


Ray::Ray()
{
	point = Vec3::Zero();
	dir = Vec3(0, 0, 1);
}

Ray::Ray(Vec3 _point, Vec3 _dir){
	point = _point;
	dir = _dir;
}


Ray::~Ray()
{
}
