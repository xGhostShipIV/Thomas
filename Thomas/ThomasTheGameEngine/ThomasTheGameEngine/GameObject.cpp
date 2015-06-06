// Author: Nathan Senter
// I forgot the original date. The new one is 05/20/2015

#include "GameObject.h"
#include "Component.h"
#include "Game.h"

GameObject::GameObject()
{
	isFlagged = false;
	
	GAME->gameObjects.push_back(this); 
}

GameObject::~GameObject()
{
}

/* Adds the first parameter to the objects component list while passing its
  address into the second parameter for use later. */
void GameObject::addComponent(Component * _newComponent, Component * _outPut)
{
	_newComponent->parentObject = this;

	components.push_back(_newComponent);
	_outPut = _newComponent;
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
template<class TYPE>
TYPE * GameObject::getComponent()
{
	for (int i = 0; i < components.size(); i++)
	{
		if (typeid(*components[i]) == typeid(TYPE))
			return (TYPE*)components[i];
	}
	return nullptr;
}

void GameObject::Destroy()
{
	isFlagged = true;
}
