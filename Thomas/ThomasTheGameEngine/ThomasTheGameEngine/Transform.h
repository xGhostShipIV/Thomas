#pragma once
#include "../Math/four_dimensions.hpp"
#include "Component.h"

/*
	A component that contains all positional information of a gameObject 
	in world space.
*/
class Transform {
public:
	GameObject * parentObject;

	Transform(GameObject * _go, Vec3 _position = Vec3::Zero(), Vec3 _scale = Vec3(1, 1, 1), Quat _rotation = Quat(1, 0, 0, 0));
	Transform(GameObject * _go, Transform& _t);

	Vec3 position;
	Vec3 scale;
	Quat rotation;
	
	//Direction vectors that can aid in object movement
	Vec3 forward();
	Vec3 up();

	//Returns the objects orientation in different formats
	Quat getQuat();
	Vec3 getEuler();

	//Transform methods
	//These will apply the given transforms and move the gameObject
	void LookAt(Vec3);
	void Rotate(Quat);
	void Rotate(Vec3);
	void Translate(Vec3);
	void Scale(Vec3);

	//Returns all components of the transform as a single matrix4
	//More or less only used for the GPU
	Matrix4 toMat4();
};