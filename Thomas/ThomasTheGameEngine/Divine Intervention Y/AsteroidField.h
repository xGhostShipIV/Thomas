#pragma once
#include <GameObject.h>

class Level;
class PlayerBall;
class Sound;

class AsteroidField :
	public GameObject
{
public:
	AsteroidField(Level *, Vec3, float _radius, float _numAsteroids);
	~AsteroidField();

	void Update(float timeStep_) override;

	virtual void SetRenderEnabled(bool isEnabled_) override;
	virtual bool GetRenderEnabled() override;
private:
	std::vector<GameObject *> asteroids;
	PlayerBall * player;
	Sound * collideSound;
};

