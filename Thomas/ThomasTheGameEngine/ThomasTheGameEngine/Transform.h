#pragma once
#include "../Math/four_dimensions.hpp"
#include "Component.h"

class Transform : public Component {
public:
	Transform(Vec3 _position = Vec3::Zero(), Vec3 _scale = Vec3(1, 1, 1), Quat _rotation = Quat());

	Vec3 position;
	Vec3 scale;
	Quat rotation;
	
	Vec3 forward();
	Vec3 up();
	Quat getQuat();
	Vec3 getEuler();

	void LookAt(Vec3);
	void Rotate(Quat);
	void Rotate(Vec3);
	void Translate(Vec3);
	void Scale(Vec3);

	Matrix4 toMat4();
};