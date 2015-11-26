#pragma once

#include "Component.h"
#include <vector>

class Particle;

class ParticleSystem : public Component
{

public:

	enum Emitter_Type
	{
		Emitter_Type_Sphere,
		Emitter_Type_Cone,
		Emitter_Type_Cube
	};

	ParticleSystem(GameObject * _owner, Emitter_Type _emitterType, std::string _modelName, std::string _textureName,
		float _maxParticles, float _rateOfEmission, float _lifeTime);

	~ParticleSystem();
	void UpdateParticles(unsigned int);
	void RenderParticles();
	void SetEmitterType(Emitter_Type);
private:

	std::vector<Particle *> particles;
	

	Emitter_Type emitter_type;

	float elapsedTime;
	float emissionRate;
};