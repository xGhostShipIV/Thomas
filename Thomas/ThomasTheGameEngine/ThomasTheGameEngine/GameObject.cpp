// Author: Nathan Senter
// I forgot the original date. The new one is 05/20/2015

#include "GameObject.h"
#include "Component.h"
#include "RenderableComponent.h"
#include "InputComponent.h"

GameObject::GameObject() : transform(Transform(this, Vec3::Zero(), Vec3(1, 1, 1), Quat(1, 0, 0, 0)))
{
	isFlagged = false;
}

GameObject::GameObject(Vec3 _position) : transform(Transform(this, _position))
{
	isFlagged = false;
}

GameObject::GameObject(Transform _t) : transform(Transform(this, _t))
{
	isFlagged = false;
}


GameObject::~GameObject()
{
}

Transform& GameObject::GetTransform()
{
	return transform;
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
		if (typeid(*components[i]) == typeid(RenderableComponent))
			return (RenderableComponent*)components[i];
	}
	return nullptr;
}

//template<>
//Transform* GameObject::getComponent()
//{
//	for (int i = 0; i < components.size(); i++)
//	{
//		if (typeid(*components[i]) == typeid(Transform))
//			return (Transform*)components[i];
//	}
//	return nullptr;
//}

template<>
InputComponent* GameObject::getComponent()
{
	for (int i = 0; i < components.size(); i++)
	{
		if (typeid(*components[i]) == typeid(InputComponent))
			return (InputComponent*)components[i];
	}
	return nullptr;
}

template<class TYPE>
TYPE* GameObject::getComponent()
{
	for (int i = 0; i < components.size(); i++)
	{
		if (typeid(*components[i]) == typeid(TYPE))
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
	}
}