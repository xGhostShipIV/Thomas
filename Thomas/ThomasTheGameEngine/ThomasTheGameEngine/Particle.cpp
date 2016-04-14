
#include "Particle.h"
#include "Level.h"

#include <stdlib.h>

Particle::Particle(Level * _level, Vec3 _startPosition, float _lifeTime, std::string _modelName, std::string _textureName, Object_Type _type)
{
	maxLifeTime = _lifeTime;
	currentLifeTime = 0.0f;

	scaleAmount = 0.5f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1.4f - 0.5f)));

	scale = Vec3(scaleAmount, scaleAmount, scaleAmount);
	
	rotationAmount = rand() % 8 - 4;

	position = _startPosition;

	renderer = new Generic_RenderableComponent(this, _modelName, _textureName);
	((Generic_RenderableComponent*)renderer)->SetEffecctedByLight(false, false, false);

	SetRenderEnabled(false);
	
	isAlive = false;

	objectType = _type;

	level = _level;
}

Particle::~Particle()
{
	delete renderer;
}

void Particle::Render()
{
	if (isAlive)
	{
		SetRenderEnabled(true);
		renderer->Render();
	}
	else
	{
		SetRenderEnabled(false);
	}
}

void Particle::Update(float _deltaTime)
{
	if (isAlive)
	{
		if (!GetRenderEnabled())
			SetRenderEnabled(true);

		if (objectType == Billboard)
			LookAt(level->currentCamera->position);

		currentLifeTime += _deltaTime;
		Rotate(Quat(rotationAmount * _deltaTime, forward()));

		position += velocity * _deltaTime;

		if (currentLifeTime >= maxLifeTime)
		{
			isAlive = false;
			SetRenderEnabled(false);

			if (isLooped)
				currentLifeTime = 0.0f;
		}
	}
}

void Particle::SetVelocity(Vec3 _velocity)
{
	velocity = _velocity;
}

void Particle::SetElapsedTime(float time_)
{
	currentLifeTime = time_;
}