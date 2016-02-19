#pragma once
#include <GameObject.h>

class Level;
class PlayerBall;

class AsteroidField :
	public GameObject
{
public:
	AsteroidField(Level *, Vec3, float _radius, float _numAsteroids);
	~AsteroidField();

	void Update(float timeStep_) override;

private:
	std::vector<GameObject *> asteroids;
	PlayerBall * player;
};

