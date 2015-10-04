#pragma once

	/* 
		An empty class that all components will inherit from.  Used to allow the use of
		a GetComponent method. 
	*/

class GameObject;

template<class _objectType> class Component
{
public:
	Component();
	~Component();

	_objectType * parentObject;
};

