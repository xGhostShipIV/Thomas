#include "FocusCamera.h"
#include <Game.h>
#include <InputHandler.h>
#include "DIY_Level.h"
#include <PhysicsWorld.h>
#include <iostream>

FocusCamera::FocusCamera(Level * level_, GameObject * focus_, Vec3 position_) : Camera(level_){
	focus = focus_;

	stateMachine.ChangeState(new ::Stare(this));
	
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

	
	//Below here lies the old switch-case state-machine. Kept for posterity and backup

	//Control behaviour of input for camera
	//Includes state traversal
	//Vec2 mouseDir_ = Input->deltaMouse();
	//switch (behaviour){
	//case(LookState::Pan) :
	//	
	//	break;
	//case (LookState::Stare) :
	//	//LookAt(focus->position);
	//	////State control from Stare		
	//	//if (Input->isMousePressed(SDL_BUTTON_RIGHT)){
	//	//	behaviour = LookState::Orbit;
	//	//}
	//	//else if (Input->isMousePressed(SDL_BUTTON_LEFT)){
	//	//	behaviour = LookState::Peek;
	//	//}

	//	//if (Input->isKeyDown(SDLK_q)){
	//	//	Rotate(Quat(deltaTime_, forward()));
	//	//}
	//	//else if (Input->isKeyDown(SDLK_e)){
	//	//	Rotate(Quat(-deltaTime_, forward()));
	//	//}

	//	//position = selfieStick.Normalized() * followDistance + focus->position;

	//	break;
	//case (LookState::Orbit) :
	//	//Rotate(Quat(mouseDir_.x * deltaTime_, Vec3::BasisY()));
	//	//selfieStick = Quat::rotate(Quat(mouseDir_.x * deltaTime_, Vec3::BasisY()), selfieStick);

	//	//Rotate(Quat(mouseDir_.y * deltaTime_, right() * -1));
	//	//selfieStick = Quat::rotate(Quat(mouseDir_.y * deltaTime_, right() * -1), selfieStick);

	//	//if (abs(Vec3::dot(up(), Vec3::BasisY())) < 0.1){
	//	//	Rotate(Quat(mouseDir_.y * deltaTime_, right()));
	//	//	selfieStick = Quat::rotate(Quat(mouseDir_.y * deltaTime_, right()), selfieStick);
	//	//}

	//	//position = selfieStick.Normalized() * followDistance + focus->position;

	//	////State control from Orbit
	//	////Don't allow traversal directly to peek from orbit
	//	//if (Input->isMouseReleased(SDL_BUTTON_RIGHT)){
	//	//	behaviour = LookState::Stare;
	//	//}
	//	break;
	//case (LookState::Peek) :

	//	break;
	//}

	stateMachine.UpdateState();
	Camera::Update(deltaTime_);
}

void FocusCamera::ChangeFocus(GameObject* newFocus_){
	focus = newFocus_;
}

GameObject * FocusCamera::getFocus(){
	return focus;
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


#define Parent static_cast<FocusCamera*>(self)


Stare::Stare(void* whoAmI): State(whoAmI){}
Stare::~Stare(){}
Peek::Peek(void* whoAmI) : State(whoAmI){}
Peek::~Peek(){}
Orbit::Orbit(void* whoAmI) : State(whoAmI){}
Orbit::~Orbit(){}

void Stare::Execute(){

	Parent->LookAt(Parent->focus->position);

	if (Input->isKeyDown(SDLK_q)){
		Parent->Rotate(Quat(Physics->getTimeStep(), Parent->forward()));
	}
	else if (Input->isKeyDown(SDLK_e)){
		Parent->Rotate(Quat(-Physics->getTimeStep(), Parent->forward()));
	}

	Parent->position = Parent->selfieStick.Normalized() * Parent->followDistance + Parent->focus->position;

	//State control from Stare		
	if (Input->isMousePressed(SDL_BUTTON_RIGHT)){
		Parent->stateMachine.ChangeState(new Orbit(Parent));
	}
	else if (Input->isMousePressed(SDL_BUTTON_LEFT)){
		Parent->stateMachine.ChangeState(new Peek(Parent));
	}
}
void Stare::onEnter(){}
void Stare::onExit(){}

void Orbit::Execute(){
	Vec2 mouseDir_ = Input->deltaMouse();

	Parent->Rotate(Quat(mouseDir_.x * Physics->getTimeStep(), Vec3::BasisY()));
	Parent->selfieStick = Quat::rotate(Quat(mouseDir_.x * Physics->getTimeStep(), Vec3::BasisY()), Parent->selfieStick);

	Parent->Rotate(Quat(mouseDir_.y * Physics->getTimeStep(), Parent->right() * -1));
	Parent->selfieStick = Quat::rotate(Quat(mouseDir_.y * Physics->getTimeStep(), Parent->right() * -1), Parent->selfieStick);

	if (abs(Vec3::dot(Parent->up(), Vec3::BasisY())) < 0.1){
		Parent->Rotate(Quat(mouseDir_.y * Physics->getTimeStep(), Parent->right()));
		Parent->selfieStick = Quat::rotate(Quat(mouseDir_.y * Physics->getTimeStep(), Parent->right()), Parent->selfieStick);
	}

	Parent->position = Parent->selfieStick.Normalized() * Parent->followDistance + Parent->focus->position;

	//State control from Orbit
	//Don't allow traversal directly to peek from orbit
	if (Input->isMouseReleased(SDL_BUTTON_RIGHT)){
		Parent->stateMachine.ChangeState(new Stare(Parent));
	}
}

void Orbit::onEnter(){}
void Orbit::onExit(){}

void Peek::Execute(){
	Vec2 mouseDir_ = Input->deltaMouse();

	Parent->Rotate(Quat(-mouseDir_.x * Physics->getTimeStep(), Vec3(0, 1.0f, 0)));
	Parent->Rotate(Quat(-mouseDir_.y * Physics->getTimeStep(), Vec3::cross(Parent->forward(), Parent->up())));

	//State control from Peek
	if (Input->isMouseReleased(SDL_BUTTON_LEFT)){
		Parent->stateMachine.ChangeState(new Stare(Parent));
	}
}
void Peek::onEnter(){
	beginningOrientation = Parent->rotation;
}
void Peek::onExit(){
	Parent->rotation = beginningOrientation;
}