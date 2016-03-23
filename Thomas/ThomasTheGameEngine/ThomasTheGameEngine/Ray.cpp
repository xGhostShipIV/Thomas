#include "Ray.h"
#include "Game.h"
#include "Level.h"
#include "InputHandler.h"
#include "GameProperties.h"
#include <iostream>


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
	Camera* view_ = Game::GetInstance()->currentLevel->currentCamera;
	point = view_->position;

	//%age of screen away from top left in each direction
	Vec2 mouseInput = Vec2(
		Input->mousePos().x / GameProperties::getInstance()->getVideoProperties()->screenWidth,
		Input->mousePos().y / GameProperties::getInstance()->getVideoProperties()->screenHeight);

	//Place point directly on transformed frustum
	Frustrum transformed = Frustrum::getTransofmedFrustrum(view_);
	
	//Assumes near plane is 0.1f away, taken from game properties
	Plane nearPlane = Plane(view_->forward() * -1, view_->forward() * 0.1f + view_->position);

	Vec3 worldPos = transformed.nearTopLeft + Vec3(
		mouseInput.x * (transformed.nearBottomRight.x - transformed.nearTopLeft.x),
		mouseInput.y * (transformed.nearBottomRight.y - transformed.nearTopLeft.y),
		0.0f);

	worldPos.z = (nearPlane.normal.x * worldPos.x + nearPlane.normal.y * worldPos.y + nearPlane.D) / nearPlane.normal.z;

	dir = (worldPos - view_->position).Normalized();

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