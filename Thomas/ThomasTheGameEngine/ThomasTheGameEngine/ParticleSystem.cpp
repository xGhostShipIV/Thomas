#include "ParticleSystem.h"
#include "Particle.h"

ParticleSystem::ParticleSystem(GameObject * _owner, Emitter_Type _emitterType, std::string _modelName, std::string _textureName,
	float _maxParticles, float _rateOfEmission, float _lifeTime) : Component(_owner, Component::ParticleSystem)
{
	for (int i = 0; i < _maxParticles; i++)
	{
		particles.push_back(new Particle(parentObject->level, parentObject->position, _lifeTime, _modelName, _textureName, Particle::Billboard));
	}

	emissionRate = _rateOfEmission;
	elapsedTime = 0.0f;

	emitter_type = _emitterType;
}

void ParticleSystem::UpdateParticles(UINT32 _deltaTime)
{
	if (elapsedTime >= emissionRate)
	{
		//Spawn new particle
		for (int i = 0; i < particles.size(); i++)
		{
			if (!particles[i]->isAlive)
			{
				particles[i]->position = parentObject->position;
				//particles[i]->scale = Vec3(1, 1, 1);
				particles[i]->SetVelocity(Vec3(0, .01f, 0));
				particles[i]->isAlive = true;
				elapsedTime = 0.0f;
				break;
			}
		}
	}
	else elapsedTime += _deltaTime / 1000.0f;


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

