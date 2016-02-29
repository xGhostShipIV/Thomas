#include "FocusCamera.h"
#include <Game.h>
#include <InputHandler.h>
#include "DIY_Level.h"
#include <PhysicsWorld.h>
#include <iostream>


FocusCamera::FocusCamera(Level * level_, GameObject * focus_, Vec3 position_) : Camera(level_){
	focus = focus_;

	behaviour = LookState::Stare;
	position = position_;
	if (focus){
		followDistance = Vec3::length(position - focus->position);
		LookAt(focus->position);
		MinCameraDistance = int(followDistance / 3.0f);
		MaxCameraDistance = int(followDistance * 3.0f);
		selfieStick = position - focus->position;
	}
}


void FocusCamera::Update(float deltaTime_) {

	//Testing output.
	//std::cout << followDistance << std::endl;

	//Mouse wheel to zoom in/out
	if (Input->mouseWheel < 0)
	{
		if (followDistance < MaxCameraDistance){
			followDistance += 1;
		}
		else {
			followDistance = MaxCameraDistance;
		}
	}
	else if (Input->mouseWheel > 0)
	{
		if (followDistance > MinCameraDistance){
			followDistance -= 1;
		}
		else {
			followDistance = MinCameraDistance;
		}
	}

	//Control behaviour of input for camera
	//Includes state traversal
	Vec2 mouseDir_ = Input->deltaMouse();
	switch (behaviour){
	case (LookState::Stare) :
		LookAt(focus->position);
		//State control from Stare
		if (Input->isMousePressed(SDL_BUTTON_RIGHT)){
			behaviour = LookState::Orbit;
		}
		else if (Input->isMousePressed(SDL_BUTTON_LEFT)){
			behaviour = LookState::Peek;
		}

		break;
	case (LookState::Orbit) :
		Physics->Orbit(focus->position, Vec3::BasisY(), this, mouseDir_.x * deltaTime_);
		Rotate(Quat(mouseDir_.x * deltaTime_, Vec3::BasisY()));
		selfieStick = Quat::rotate(Quat(mouseDir_.x * deltaTime_, Vec3::BasisY()), selfieStick);

		//State control from Orbit
		//Don't allow traversal directly to peek from orbit
		if (Input->isMouseReleased(SDL_BUTTON_RIGHT)){
			behaviour = LookState::Stare;
		}
		break;
	case (LookState::Peek) :

		Rotate(Quat(-mouseDir_.x * deltaTime_, Vec3(0, 1.0f, 0)));
		Rotate(Quat(-mouseDir_.y * deltaTime_, Vec3::cross(forward(),up())));

		//State control from Peek
		if (Input->isMouseReleased(SDL_BUTTON_LEFT)){
			behaviour = LookState::Stare;
		}
		break;
	}

	position = selfieStick.Normalized() * followDistance + focus->position;

	Camera::Update(deltaTime_);
}

void FocusCamera::ChangeFocus(GameObject* newFocus_){
	focus = newFocus_;
}

void FocusCamera::ChangeDistance(float newFollow_){
	followDistance = newFollow_;
}

void FocusCamera::SetMaxDistance(float maxDistance_){
	MaxCameraDistance = maxDistance_;
}
void FocusCamera::SetMinDistance(float minDistance_){
	MinCameraDistance = minDistance_;
}