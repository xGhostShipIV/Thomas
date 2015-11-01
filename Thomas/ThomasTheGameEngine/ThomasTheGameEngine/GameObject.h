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
private:
	Transform transform;
public:
	//Various constructors to set the starting position of a gameObject
	GameObject();
	GameObject(Vec3 _position);
	GameObject(Transform _t);
	~GameObject();

	Transform& GetTransform();

	//Render and update functionalities specific to the gameObject
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

	//Removes the specified component from the gameObject
	void removeComponent(Component *);

	//Adds a string tag to the gameObject. Tags can be used
	//as an easy way to identify gameObjects from outside itself
	void addTag(Tag);

	//Adds or removes gameObjects as children
	void addChild(GameObject *);
	void removeChild(GameObject *);

	//Checks whether the game object has given tag
	bool hasTag(Tag);

	//Triggers the isFlagged boolean
	void Destroy();

	/**********************************************/
	//NOTE: This method is still under development// 
	/**********************************************/

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



};

