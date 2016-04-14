#include "ParticleSystem.h"
#include "Random.h"

ParticleSystem::ParticleSystem(GameObject * _owner, Emitter_Type _emitterType, std::string _modelName, std::string _textureName,
	float _maxParticles, float _rateOfEmission, float _lifeTime, Particle::Object_Type _type, bool isLooped_ = false) : Component(_owner, Component::ParticleSystem)
{
	for (int i = 0; i < _maxParticles; i++)
	{
		particles.push_back(new Particle(parentObject->level, parentObject->position, _lifeTime, _modelName, _textureName, _type));
	}

	iVeloctiy = Vec3::Zero();
	positionOffset = Vec3::Zero();
	iScale = Vec3(1, 1, 1);

	emissionRate = _rateOfEmission;
	elapsedTime = 0.0f;

	emitter_type = _emitterType;

	isActive = true;
}

ParticleSystem::~ParticleSystem()
{

}

void ParticleSystem::UpdateParticles(float _deltaTime)
{
	if (isActive)
	{
		if (elapsedTime >= emissionRate)
		{
			//Spawn new particle
			for (int i = 0; i < particles.size(); i++)
			{
				if (!particles[i]->isAlive)
				{
					particles[i]->position = parentObject->position + positionOffset;
					particles[i]->scale = iScale;
					particles[i]->rotation = iRotation;
					particles[i]->isLooped = isLooped;

					if (emitter_type == Emitter_Type_Cone)
					{
						float theta = Random::box_muller(0, 22.5);
						float y = sin(theta);
						float x = cos(theta);

						Vec3 v = Vec3(x, y, 0);

						Quat::rotate(Quat(Vec3::dot(v, iVeloctiy), Vec3::cross(v, iVeloctiy)), v);

						particles[i]->SetVelocity(v);
					}
					else
						particles[i]->SetVelocity(iVeloctiy);

					particles[i]->isAlive = true;
					elapsedTime = 0.0f;
					break;
				}
			}
		}
		else elapsedTime += _deltaTime;
	}

	//Update living particles
	for (int i = 0; i < particles.size(); i++)
	{
		particles[i]->Update(_deltaTime);
	}
}

void ParticleSystem::RenderParticles()
{
	for (int i = 0; i < particles.size(); i++)
	{
		particles[i]->Render();
	}
}

void ParticleSystem::SetEmitterType(Emitter_Type _type)
{
	emitter_type = _type;
}

void ParticleSystem::Play()
{
	isActive = true;

	for (int i = 0; i < particles.size(); i++)
		particles[i]->SetElapsedTime(0);
}

void ParticleSystem::Stop()
{
	isActive = false;
}

void ParticleSystem::SetInitialRotation(Quat _rot)
{
	iRotation = _rot;
}

void ParticleSystem::SetInitialVelocity(Vec3 _vel)
{
	iVeloctiy = _vel;
}

void ParticleSystem::SetPositionOffset(Vec3 _pos)
{
	positionOffset = _pos;
}

void ParticleSystem::SetInitialScale(Vec3 _scale)
{
	iScale = _scale;
}

bool ParticleSystem::isPlaying()
{
	return isActive;
}