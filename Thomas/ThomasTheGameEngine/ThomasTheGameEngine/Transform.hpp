#include "four_dimensions.hpp"

class Transform : Component {
public:
	Vec3 position;
	Vec3 scale;
	Vec3 rotation;
	
	Vec3 forward();
	Vec3 up();
	Quat getQuat();
	Vec3 getEuler();
	void LookAt(Vec3);
	void Rotate(Quat);
	void Rotate(Vec3);
	void Translate(Vec3);
	void Scale(Vec3);
	Matrix4 CameraTransform();
}