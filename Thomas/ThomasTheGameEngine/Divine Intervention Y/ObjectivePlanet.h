#pragma once

#include <GameObject.h>
#include <Rigidbody.h>
#include <RenderableComponent.h>

typedef std::string string;

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

	string planetName;
	string planetDescription;

	Vec3 orbitAxis;
};

