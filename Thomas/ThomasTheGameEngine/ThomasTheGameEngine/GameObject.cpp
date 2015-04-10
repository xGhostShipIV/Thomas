#include "GameObject.h"
#include "Component.h"

GameObject::GameObject()
{
}


GameObject::~GameObject()
{
}

Component * GameObject::addComponent(Component * _c)
{
	components.push_back(_c);
	return _c;
}
