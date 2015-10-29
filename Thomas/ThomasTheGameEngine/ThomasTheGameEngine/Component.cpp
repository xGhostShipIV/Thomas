#include "Component.h"

Component::Component(GameObject * _go)
{
	parentObject = _go;
}

Component::~Component()
{
}