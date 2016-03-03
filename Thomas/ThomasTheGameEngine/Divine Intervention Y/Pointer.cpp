#include "Pointer.h"
#include "PlayerBall.h"

#include <InputHandler.h>
#include <PhysicsWorld.h>
#include <Game.h>
#include "DIY_Level.h"
#include <iostream>

Pointer::Pointer(Level * level_, Vec3 position_, PlayerBall * player_) : GameObject(level_, position_), followCam(false)
{
	renderer = new RenderableComponent("pointer", "white", this);
	//renderer->SetEffecctedByLight(false, false, false);

	Scale(Vec3(0.14f, 0.14f, 0.14f));

	ball = player_;
}


Pointer::~Pointer()
{
}

void Pointer::Update(float timeStep_)
{
	GameObject::Update(timeStep_);

	position.y = ball->position.y;

	if (Input->isKeyDown(SDLK_RIGHT) || Input->isKeyDown(SDLK_a))
	{
		PhysicsWorld::Orbit(ball->position, Vec3(0, 1, 0), this, 3 * timeStep_);
	}
	if (Input->isKeyDown(SDLK_LEFT) || Input->isKeyDown(SDLK_d))
	{
		PhysicsWorld::Orbit(ball->position, Vec3(0, 1, 0), this, -3 * timeStep_);
	}

	if (Input->isKeyReleased(SDLK_k))
		followCam = !followCam;

	if (Input->isMouseDown(SDL_BUTTON_RIGHT) && followCam)
	{
		//Align pointer with camera
		position = ball->position + Vec3(level->currentCamera->position.x - ball->position.x, 0, level->currentCamera->position.z - ball->position.z).Normalized() * 2;
	}

	LookAt(ball->position);
	Rotate(Quat(M_PI / 2.0f, Vec3(0, 1, 0)));

	if (((DIY_Level*)GAME->currentLevel)->levelState == DIY_Level_State::PLAYING &&
		((DIY_Level*)GAME->currentLevel)->playingState == DIY_Level_Playing_State::SHOOTING)
	{
		if (!isEnabled)
		{
			position = ball->position + Vec3(level->currentCamera->position.x - ball->position.x, 0, level->currentCamera->position.z - ball->position.z).Normalized() * 2;
		}
		isEnabled = true;
	}
	else
		isEnabled = false;
}

void Pointer::Render()
{
	if (isEnabled)
		GameObject::Render();
}