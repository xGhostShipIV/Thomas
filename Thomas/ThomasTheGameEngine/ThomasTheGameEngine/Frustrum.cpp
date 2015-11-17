#include "Frustrum.h"
#include "Camera.h"
#include "GameProperties.h"

Frustrum::Frustrum()
{
	float zFar = GameProperties::getVideoProperties()->drawDistance;
	float znear = 0.1f;
	float fov = 45.0f;
	float aspectRatio = GameProperties::getVideoProperties()->aspectRatio();

	nearBottomRight = Vec3(znear * tan(fov * aspectRatio / 2.0f), znear * -tan(fov / 2.0f), znear);
	nearTopLeft = Vec3(znear * -tan(fov * aspectRatio / 2.0f), znear * tan(fov / 2.0f), znear);

	farBottomRight = Vec3(zFar * tan(fov * aspectRatio / 2.0f), zFar * -tan(fov / 2.0f), zFar);
	farTopLeft = Vec3(zFar * -tan(fov * aspectRatio / 2.0f), zFar * tan(fov / 2.0f), zFar);
}

Frustrum::~Frustrum()
{

}

Frustrum Frustrum::getTransofmedFrustrum(Camera * _camera)
{
	Frustrum f;

	f.nearBottomRight = Vec4::DownCast(_camera->toMat4() * Vec4::HomoVec3(f.nearBottomRight));
	f.nearTopLeft = Vec4::DownCast(_camera->toMat4() * Vec4::HomoVec3(f.nearTopLeft));

	f.farBottomRight = Vec4::DownCast(_camera->toMat4() * Vec4::HomoVec3(f.farBottomRight));
	f.farTopLeft = Vec4::DownCast(_camera->toMat4() * Vec4::HomoVec3(f.farTopLeft));

	return f;
}

void Recalculate()
{
	Frustrum();
}