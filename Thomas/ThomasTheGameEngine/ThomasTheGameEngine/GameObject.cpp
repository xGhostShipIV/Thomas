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

template<class TYPE>
Component* GameObject::getComponent(TYPE _component)
{	
	for (int i = 0; i < components.size(); i++)
	{
		if (typeid(*components[i]) == typeid(_component))
			return components[i];
	}
	
}
