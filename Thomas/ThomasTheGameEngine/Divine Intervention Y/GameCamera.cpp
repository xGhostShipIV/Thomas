#include "GameCamera.h"
#include <Game.h>
GameCamera::GameCamera(Level * level_, Vec3 position_, Vec3 lookAt_) : Camera(level_)
{
	position = position_;
	LookAt(lookAt_);

	mouseDown = false;
	originalLookat = forward();

	cf = new Camera_Forward(this, SDLK_w);
	cb = new Camera_Back(this, SDLK_s);
	cl = new Camera_Left(this, SDLK_a);
	cr = new Camera_Right(this, SDLK_d);

	lc = new LeftClick(this, Game::GetInstance()->inputManager->mouseButtonDict[SDL_BUTTON_LEFT]);

	lu = new Look_Up(this, MouseMovement::Negative_Y);
	ld = new Look_Down(this, MouseMovement::Positive_Y);
	lr = new Look_Right(this, MouseMovement::Negative_X);
	ll = new Look_Left(this, MouseMovement::Positive_X);
}

GameCamera::~GameCamera()
{
	GameObject::~GameObject();
}

void GameCamera::Update(float deltaTime_)
{
	//If youre no longer holding the mouse and have rotated, this section will rotate back
	if (!mouseDown)
		if (forward() != originalLookat)
		{
			LookAt(originalLookat);
			//originalLookat = forward();
		}

	Camera::Update(deltaTime_);
}