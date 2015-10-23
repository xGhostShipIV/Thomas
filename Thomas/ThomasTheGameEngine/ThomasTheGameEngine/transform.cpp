#include "Transform.hpp"

void Transform::Translate(Vec3 _translate){
	position += _translate;
	for (auto it = parentObject->childObjects.begin(); it != parentObject->childObjects.end(); it++){
		(*it)->getComponent<Transform>()->Translate(_translate);
	}
	
}

void Transform::Scale(Vec3 _scale){
	scale += _scale;
	for (auto it = parentObject->childObjects.begin(); it != parentObject->childObjects.end(); it++){
		if ((*it)->getComponent<Transform>()){
			(*it)->getComponent<Transform>()->Scale(_scale);
		}
	}
}

void Transform::Rotate(Quat _rotation){
	//If problem exists, change order, internet says it should be fine
	rotation = rotation * _rotation;
	for (auto it = parentObject->childObjects.begin(); it != parentObject->childObjects.end(); it++){
		if ((*it)->getComponent<Transform>()){
			(*it)->getComponent<Transform>()->Rotate(_rotation);
		}
	}
}

//Rotates in the X-Y-Z plane (in that order) use Radians, if possible use the Rotate(Quat) method instead
void Transform::Rotate(Vec3 _rotation){
	rotation = rotation * Quat(_rotation.x, Vec3::BasisX()) * Quat(_rotation.y, Vec3::BasisY()) * Quat(_rotation.z, Vec3::BasisZ());
	for (auto it = parentObject->childObjects.begin(); it != parentObject->childObjects.end(); it++){
		(*it)->getComponent<Transform>()->Rotate(_rotation);
	}
}

Matrix4 Transform::toMat4() {
	return Matrix4::Translate(position.x, position.y, position.z) * Matrix4::Rotate(rotation) * Matrix4::Scale(scale.x, scale.y, scale.z);
}

Quat Transform::getQuat(){
	return rotation;
}

//Should not be using euler angles, included for completness
Vec3 Transform::getEuler(){
	return Vec3(
		atan(2 * (rotation.w * rotation.vector.x + rotation.vector.y * rotation.vector.z) / (rotation.w * rotation.w - rotation.vector.x * rotation.vector.x - rotation.vector.y * rotation.vector.y + rotation.vector.z * rotation.vector.z)),
		-asin(2 * (rotation.vector.x * rotation.vector.z - rotation.w * rotation.vector.y)),
		atan(2 * (rotation.w * rotation.vector.z + rotation.vector.x * rotation.vector.y) / (rotation.w * rotation.w + rotation.vector.x * rotation.vector.x - rotation.vector.y * rotation.vector.y - rotation.vector.z * rotation.vector.z))
		);
}

Vec3 Transform::forward(){
	return rotation.vector;
}

//Works according to the internet, needs testing.
Vec3 Transform::up() {
	return Quat::rotate(rotation,Vec3::BasisY());
}

void Transform::LookAt(Vec3 _target){
	Vec3 pointToTarget = position - _target;
	rotation = Quat(2 * acos(rotation.w), pointToTarget);
}