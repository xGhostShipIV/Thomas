#pragma once

#include <GameObject.h>
#include <Rigidbody.h>
#include <RenderableComponent.h>

typedef std::string string;

class Sound;

class ObjectivePlanet : public GameObject
{
public:
	enum Orbit_Angle{
		Horizonal,
		Vertical
	};

	ObjectivePlanet(Level *, GameObject * hostPlanet, string textureName_, Orbit_Angle);
	~ObjectivePlanet();

	void Update(float timeStep_);

private:
	RenderableComponent * renderer;
	Rigidbody * rigidBody;
	GameObject * planetToOrbit;
	Rigidbody * playerRigidBody;

	string planetName;
	string planetDescription;

	Vec3 orbitAxis;

	const float FORCE_REQUIRED_TO_DESTROY = 1.0f;

	Sound * sound;
};

