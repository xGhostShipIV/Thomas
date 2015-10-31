// Author: Nathan Senter
// I forgot the original date. The new one is 05/20/2015

#pragma once
#include <vector>
#include <string>
#include <typeinfo>
#include <glew.h>
#include <freeglut.h>
#include "Transform.h"

class Component;

typedef std::string Tag;

class GameObject
{
public:
	GameObject();
	GameObject(Vec3 _position);
	GameObject(Transform _t);
	~GameObject();

	virtual void Render();
	virtual void Update(UINT32 _deltaTime){};

	//Flag that sets object for removal from game
	bool isFlagged;

	//A list of ALL the gameObjects components
	std::vector<Component *> components;

	//List of all tags applied to this game object
	std::vector<Tag> Tags;

	//List of all objects that are children of this object
	std::vector<GameObject *> childObjects;

	Transform * transform;

	void removeComponent(Component *);

	void addTag(Tag);

	void addChild(GameObject *);
	void removeChild(GameObject *);

	//Checks whether the game object has given tag
	bool hasTag(Tag);

	//Returns the address to a given component type
	template<class TYPE> TYPE* getComponent();
	/*{
		for (int i = 0; i < components.size(); i++)
		{
			if (typeid(*components[i]) == typeid(TYPE))
			return (TYPE*)components[i];

		}
		return nullptr;
	}*/

	//Triggers the isFlagged boolean
	void Destroy();

};

