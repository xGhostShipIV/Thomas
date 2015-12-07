#pragma once
	/* 
		An empty class that all components will inherit from.  Used to allow the use of
		a GetComponent method. 
	*/

class GameObject;

class Component
{
public:

	enum ComponentType
	{
		Input, Renderable, Light, Rigidbody, ParticleSystem, Flipbook, Collision
	};

	Component(GameObject *, ComponentType);
	~Component();

	GameObject * parentObject;
	ComponentType type;
};

