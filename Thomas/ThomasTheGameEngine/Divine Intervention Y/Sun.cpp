#include "Sun.h"
#include <Colour.h>
#include <PhysicsWorld.h>
#include <Level.h>
#include <AudioManager.h>

#include "PlayerBall.h"
#include "DIY_Level.h"
#include <InputHandler.h>
#include <iostream>
#include <Random.h>

Sun::Sun(Level * level_, Vec3 position_, float radius_) : GameObject(level_, position_), ballHitIntoSun(false)
{
	renderer = new Sun_RenderableComponent(this, "sun");
	renderer->intensity = (MINIMUM_INTENSITY + MAXIMUM_INTENSITY) / 2.0f;

	Scale(Vec3::One() * radius_);

	light = new Light(this, Colour(75, 75, 75), Light::Point);

	rigidBody = new Rigidbody(this, new SphereCollider(this));
	rigidBody->isKinematic = false;
	static_cast<SphereCollider *>(rigidBody->col)->collisionRadius = 1.5f;
	
	Audio->loadSound("whoosh", "Sounds/firewhoosh.wav");
}


Sun::~Sun()
{
}

void Sun::Update(float timeStep_)
{
	if (InputController::getInstance()->isKeyReleased(SDLK_KP_PLUS))
	{
		renderer->intensity += 0.1f;
		std::cout << "Sun Intensity: " << renderer->intensity << "\n";
	}
	else if (InputController::getInstance()->isKeyReleased(SDLK_KP_MINUS))
	{
		renderer->intensity -= 0.1f;
		std::cout << "Sun Intensity: " << renderer->intensity << "\n";
	}

	renderer->intensity += Random::box_muller(0, INTENSITY_INCREMENT) * timeStep_;
	renderer->intensity = renderer->intensity > MAXIMUM_INTENSITY ? MAXIMUM_INTENSITY : renderer->intensity < MINIMUM_INTENSITY ? MINIMUM_INTENSITY: renderer->intensity;
	//std::cout << "Sun Intensity: " << renderer->intensity << "\n";
	
	renderer->offset -= Vec3(0.1f, 0.01f, 0.25f) * timeStep_;

	if (!player)
	{
		player = static_cast<PlayerBall *>(level->FindGameObjectWithTag("player"));
		playerRigidBody = player->getComponent<Rigidbody>();
	}

	Rotate(Quat(0.5f * timeStep_, Vec3(0, 1, 0)));
}