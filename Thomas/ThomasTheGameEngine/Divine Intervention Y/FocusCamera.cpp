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

	xInverted = 1;
	yInverted = 1;
	lookSpeed = 1.f;
}

void FocusCamera::Update(float deltaTime_) {

	if (Physics->isPhysicsRunning) { stateMachine.UpdateState(); }
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

void FocusCamera::startPan(float duration_, Wormhole* target){
	stateMachine.ChangeState(new Refocus(duration_,target, this));
}



//-----------------------------------------------States for the focus camera below here
#define Parent static_cast<FocusCamera*>(self)


Stare::Stare(void* whoAmI): State(whoAmI){}
Stare::~Stare(){}
Peek::Peek(void* whoAmI) : State(whoAmI){}
Peek::~Peek(){}
Orbit::Orbit(void* whoAmI) : State(whoAmI){}
Orbit::~Orbit(){}
Refocus::Refocus(float duration, Wormhole* targetLayer_, void* whoAmI) : State(whoAmI) {
	maxTime = duration;
	guidance = targetLayer_;
	isNewLayerSet = false;
}
Refocus::~Refocus(){}

void Stare::Execute(){

	Parent->LookAt(Parent->focus->position);

	//Mouse wheel to zoom in/out
	if (Input->mouseWheel < 0)
	{
		if (Parent->followDistance < Parent->MaxCameraDistance){
			Parent->followDistance += 1;
		}
		else {
			Parent->followDistance = Parent->MaxCameraDistance;
		}
	}
	else if (Input->mouseWheel > 0)
	{
		if (Parent->followDistance > Parent->MinCameraDistance){
			Parent->followDistance -= 1;
		}
		else {
			Parent->followDistance = Parent->MinCameraDistance;
		}
	}

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
	Vec2 mouseDir_ = Input->deltaMouse() * Parent->lookSpeed;

	Parent->Rotate(Quat(mouseDir_.x * Parent->xInverted * Physics->getTimeStep(), Vec3::BasisY()));
	Parent->selfieStick = Quat::rotate(Quat(mouseDir_.x * Parent->xInverted * Physics->getTimeStep(), Vec3::BasisY()), Parent->selfieStick);

	Parent->Rotate(Quat(-mouseDir_.y * Parent->yInverted * Physics->getTimeStep(), Parent->right() * -1));
	Parent->selfieStick = Quat::rotate(Quat(-mouseDir_.y * Parent->yInverted * Physics->getTimeStep(), Parent->right() * -1), Parent->selfieStick);

	if (Vec3::dot(Parent->up(), Vec3::BasisY()) < 0){
		Parent->Rotate(Quat(-mouseDir_.y * Parent->yInverted * Physics->getTimeStep(), Parent->right()));
		Parent->selfieStick = Quat::rotate(Quat(-mouseDir_.y * Parent->yInverted * Physics->getTimeStep(), Parent->right()), Parent->selfieStick);
	}

	Parent->position = Parent->selfieStick.Normalized() * Parent->followDistance + Parent->focus->position;

	//State control from Orbit
	//Don't allow traversal directly to peek from orbit
	if (Input->isMouseReleased(SDL_BUTTON_RIGHT)){
		Parent->stateMachine.ChangeState(new Stare(Parent));
	}

	if (Input->mouseWheel < 0)
	{
		if (Parent->followDistance < Parent->MaxCameraDistance){
			Parent->followDistance += 1;
		}
		else {
			Parent->followDistance = Parent->MaxCameraDistance;
		}
	}
	else if (Input->mouseWheel > 0)
	{
		if (Parent->followDistance > Parent->MinCameraDistance){
			Parent->followDistance -= 1;
		}
		else {
			Parent->followDistance = Parent->MinCameraDistance;
		}
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

void Refocus::Execute(){

	//Rotate around the centre point
	PhysicsWorld::Orbit(centrePos, Vec3::cross(guidance->getDestinationLayer()->position + guidance->destinationLocation + Vec3(0, 1.5f, 0) - centrePos, Vec3::BasisY()).Normalized(), Parent, -M_PI * Physics->getTimeStep() / maxTime);

	curTime += Physics->getTimeStep();
	if (curTime / maxTime >= 0.5f && !isNewLayerSet){ 
		static_cast<DIY_Level*>(Game::GetInstance()->currentLevel)->SetLayerPlane(guidance->getDestinationLayer());
		Parent->focus->position = guidance->getDestinationLayer()->position + guidance->destinationLocation + Vec3(0, 1.5f, 0);
		isNewLayerSet = true;
	}

	if (curTime >= maxTime) { Parent->stateMachine.ChangeState(new Stare(Parent)); }
}

void Refocus::onEnter(){
	//travelDistanceStep = ((Parent->getFocus()->position + Parent->selfieStick * Parent->followDistance) - Parent->position) / maxTime;
	Parent->focus->getComponent<Rigidbody>()->isKinematic = false;
	centrePos = Parent->position + (guidance->getDestinationLayer()->position + guidance->destinationLocation + Vec3(0, 1.5f, 0)) / 2;
}

void Refocus::onExit(){
	Parent->focus->getComponent<Rigidbody>()->isKinematic = true;
	//Parent->focus->position = destination->position
	Parent->position = Parent->selfieStick.Normalized() * Parent->followDistance + Parent->focus->position;
}