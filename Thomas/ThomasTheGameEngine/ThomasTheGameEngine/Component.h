#pragma once
	/* 
		An empty class that all components will inherit from.  Used to allow the use of
		a GetComponent method. 
	*/

class GameObject;

class Component
{
public:
	Component(GameObject *);
	~Component();

	GameObject * parentObject;
};

