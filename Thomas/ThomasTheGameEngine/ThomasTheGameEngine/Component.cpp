#include "Component.h"
#include "GameObject.h"

Component::Component(GameObject * _go)
{
	if (_go)
	{
		parentObject = _go;
		_go->components.push_back(this);
	}	
}

Component::~Component()
{
}