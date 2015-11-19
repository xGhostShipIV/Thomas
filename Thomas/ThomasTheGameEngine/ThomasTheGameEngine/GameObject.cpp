// Author: Nathan Senter
// I forgot the original date. The new one is 05/20/2015

#include "GameObject.h"
#include "Component.h"
#include "RenderableComponent.h"
#include "InputComponent.h"
#include "Light.h"
#include <iostream>
#include "LightManager.h"

void GameObject::Translate(Vec3 _translate){
	position += _translate;
	for (auto it = childObjects.begin(); it != childObjects.end(); it++){
		(*it)->Translate(_translate);
	}
}

void GameObject::Scale(Vec3 _scale){
	scale = Vec3(scale.x * _scale.x, scale.y * _scale.y, scale.z * _scale.z);
	for (auto it = childObjects.begin(); it != childObjects.end(); it++){	
		(*it)->Scale(_scale);
	}
}

void GameObject::Rotate(Quat _rotation){

	_rotation = _rotation.NormalizeThis();

	//If problem exists, change order, internet says it should be fine
	rotation = _rotation * rotation;
	for (auto it = childObjects.begin(); it != childObjects.end(); it++){
		//Children don't quite rotate at the right pace.
		(*it)->Rotate(_rotation);
		Vec3 newPos = (*it)->position - position;
		(*it)->position = newPos.magnitude() * Quat::rotate(_rotation, newPos).Normalized();
	}
}

//Rotates in the X-Y-Z plane (in that order) use Radians, if possible use the Rotate(Quat) method instead
void GameObject::Rotate(Vec3 _rotation){
	rotation = rotation * Quat(_rotation.x, Vec3::BasisX()) * Quat(_rotation.y, Vec3::BasisY()) * Quat(_rotation.z, Vec3::BasisZ());

	for (auto it = childObjects.begin(); it != childObjects.end(); it++){
		(*it)->Rotate(_rotation);
	}
}

Matrix4 GameObject::toMat4() {
	return Matrix4::Translate(position.x, position.y, position.z) * Matrix4::Rotate(rotation) * Matrix4::Scale(scale.x, scale.y, scale.z);
}

Quat GameObject::getQuat(){
	return rotation;
}

//Should not be using euler angles, included for completness
Vec3 GameObject::getEuler(){
	return Vec3(
		atan(2 * (rotation.w * rotation.vector.x + rotation.vector.y * rotation.vector.z) / (rotation.w * rotation.w - rotation.vector.x * rotation.vector.x - rotation.vector.y * rotation.vector.y + rotation.vector.z * rotation.vector.z)),
		-asin(2 * (rotation.vector.x * rotation.vector.z - rotation.w * rotation.vector.y)),
		atan(2 * (rotation.w * rotation.vector.z + rotation.vector.x * rotation.vector.y) / (rotation.w * rotation.w + rotation.vector.x * rotation.vector.x - rotation.vector.y * rotation.vector.y - rotation.vector.z * rotation.vector.z))
		);
}

Vec3 GameObject::forward(){
	return Quat::rotate(rotation, Vec3::BasisZ());
}

//Works according to the internet, needs testing.
Vec3 GameObject::up() {
	return Quat::rotate(rotation, Vec3::BasisY());
}

void GameObject::LookAt(Vec3 _target){
	Vec3 pointToTarget = (_target - position).Normalized();

	rotation = Quat(acos(Vec3::dot(forward(), pointToTarget)), Vec3::cross(forward(), pointToTarget));
}


GameObject::GameObject() : position(Vec3::Zero()), scale(Vec3(1, 1, 1)), rotation(Quat(1, 0, 0, 0))
{
	isFlagged = false;
}

GameObject::GameObject(Vec3 _position) : position(_position), scale(Vec3(1, 1, 1)), rotation(Quat(1, 0, 0, 0))
{
	isFlagged = false;
}


GameObject::~GameObject()
{
}

GameObject& GameObject::GetTransform()
{
	return *this;
}


/* Removes parameter component from list of components and deletes it from memory */
void GameObject::removeComponent(Component * _c)
{
	for (auto it = components.begin(); it != components.end(); it++)
	{
		if (*it._Ptr == _c)
		{
			components.erase(it);
			delete _c;
			break;
		}
	}
}

void GameObject::addTag(Tag _tag)
{
	Tags.push_back(_tag);
}

/* Attaches passed game object to this game object. */
void GameObject::addChild(GameObject * _object)
{
	childObjects.push_back(_object);
}

void GameObject::removeChild(GameObject * _object)
{
	for (auto it = childObjects.begin(); it != childObjects.end(); it++)
	{
		if (*it._Ptr == _object)
		{
			childObjects.erase(it);
			break;
		}
	}
}

/* Returns true if the game objects list of tags contains the given tag. */
bool GameObject::hasTag(Tag _tag)
{
	for (int i = 0; i < Tags.size(); i++)
	{
		if (Tags[i] == _tag)
			return true;
	}
	return false;
}

/* Returns a pointer to the first component found of the given type. */

void GameObject::Destroy()
{
	isFlagged = true;
}

template<>
RenderableComponent* GameObject::getComponent()
{
	for (int i = 0; i < components.size(); i++)
	{
		if ((*components[i]).type == Component::ComponentType::Renderable)
			return (RenderableComponent*)components[i];
	}
	return nullptr;
}

template<>
InputComponent* GameObject::getComponent()
{
	for (int i = 0; i < components.size(); i++)
	{
		if ((*components[i]).type == Component::ComponentType::Input)
			return (InputComponent*)components[i];
	}
	return nullptr;
}

template<>
Light* GameObject::getComponent()
{
	for (int i = 0; i < components.size(); i++)
	{
		if ((*components[i]).type == Component::ComponentType::Light)
			return (Light*)components[i];
	}
	return nullptr;
}

template<class TYPE>
TYPE* GameObject::getComponent()
{
	for (int i = 0; i < components.size(); i++)
	{
		if (typeid(*components[i]).name() == typeid(TYPE).name())
			return (TYPE*)components[i];
	}
	return nullptr;
}

void GameObject::Render()
{
	RenderableComponent* renderable = getComponent<RenderableComponent>();

	if (renderable)
	{
		renderable->DrawModel();
		//renderable->DrawWireframe();
	}
}

void GameObject::PreRender()
{
	Light * light = getComponent<Light>();

	if (light)
	{
		light->PushLight();
	}
}