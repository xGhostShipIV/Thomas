#pragma once
#include <vector>
#include <typeinfo>

class Component;

class GameObject
{
public:
	GameObject();
	~GameObject();

	virtual void Draw() = 0;
	virtual void Update(float _deltaTime) = 0;

	//A list of ALL the gameObjects components
	std::vector<Component *> components;

	//NOT IMPLEMENTED:
	//Transform * transform;


	//The way i see this used is:
	//  xComponent * _c = addComponent(new xComponent());
	//That way, it adds itself to the list without us having to worry about it,
	//but it also returns the address for storage in a variable.
	Component * addComponent(Component *);

	//Sexy bitch.
	template<class TYPE>
	Component * getComponent(TYPE _component){
		for (int i = 0; i < components.size(); i++){
			if (typeid(*components[i]) == typeid(TYPE))
				return components[i];
		}
	}
};

