#include "Ray.h"
#include "Game.h"
#include "Level.h"
#include "InputHandler.h"


Ray::Ray()
{
	point = Vec3::Zero();
	dir = Vec3(0, 0, 1);
}

Ray::Ray(Vec3 _point, Vec3 _dir){
	point = _point;
	dir = _dir;
}

Ray Ray::fromScreen(){
	Camera view_ = *(Game::GetInstance()->currentLevel->currentCamera);
	point = view_.position;
	dir = Quat::rotate(view_.rotation, Vec3(Input->mousePos().x, Input->mousePos().y, view_.frustrum.nearBottomRight.z));
	return Ray(point, dir);
}


Ray::~Ray()
{
}

bool Ray::castTo(Plane target_, Vec3 &output_) {
	//Ray is parrallel to plane
	if (Vec3::dot(target_.normal, dir) == 0) {
		return false;
	}

	if (target_.DistanceToPoint(point) < 0) {
		if (Vec3::dot(target_.normal, dir) > 0) {
			output_ = point + dir * (-(Vec3::dot(point, target_.normal) + target_.D) / Vec3::dot(target_.normal, dir));
			return true;
		} else {
			return false;
		}
	} else {
		if (Vec3::dot(target_.normal, dir) < 0) {
			output_ = point + dir * (-(Vec3::dot(point, target_.normal) + target_.D) / Vec3::dot(target_.normal, dir));
			return true;
		} else {
			return false;
		}
	}
	
}