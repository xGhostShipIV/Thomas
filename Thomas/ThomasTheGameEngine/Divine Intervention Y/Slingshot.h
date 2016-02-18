#include <Rigidbody.h>

class Slingshot {
private:
	Rigidbody* cueball;
	GameObject* planetoid;
	
	float totalAngle;
	float stepAngle;
	Quat orbitQuat;

	Slingshot();
public:
	bool isCaught;

	Slingshot(Rigidbody*, GameObject*);
	~Slingshot(){}

	void Update(float deltatime_);
};