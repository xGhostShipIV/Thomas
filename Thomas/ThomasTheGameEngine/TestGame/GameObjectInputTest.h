#pragma once
#include <InputComponent.h>
#include <GameObject.h>
#include <Colour.h>

#define ObjectSpeed 2.5f

class GameObject_PosX : public InputComponent {

	GameObject* go;

public:
	GameObject_PosX(GameObject* _go, SDL_Keycode key) : go(_go), InputComponent(_go, key) {};
	void whenPressed(float _timestep){
		go->Translate(Vec3(ObjectSpeed, 0, 0) * _timestep);
	}
};

class GameObject_NegX : public InputComponent {

	GameObject* go;

public:
	GameObject_NegX(GameObject* _go, SDL_Keycode key) : go(_go), InputComponent(_go, key) {};
	void whenPressed(float _timestep){
		go->Translate(Vec3(-ObjectSpeed, 0, 0) * _timestep);
	}
};

class GameObject_ScaleUp : public InputComponent {

	GameObject* go;

public:
	GameObject_ScaleUp(GameObject* _go, SDL_Keycode key) : go(_go), InputComponent(_go, key) {};
	void whenPressed(float _timestep){
		go->Scale(Vec3(1, 1, 1) + Vec3(1, 1, 1) * _timestep);
	}
};

class GameObject_ScaleDown : public InputComponent {

	GameObject* go;

public:
	GameObject_ScaleDown(GameObject* _go, SDL_Keycode key) : go(_go), InputComponent(_go, key) {};
	void whenPressed(float _timestep){
		if (_timestep >= 1) _timestep = 0.999f;
		go->Scale(Vec3(1, 1, 1) - Vec3(1, 1, 1) * _timestep);
	}
};

class AmbientBrightnessDown : public InputComponent {

	Colour* color;

public:
	AmbientBrightnessDown(Colour* _color, SDL_Keycode key) : color(_color), InputComponent(nullptr, key) {};
	void whenPressed(float _timestep){
		*color -= Colour(0.25f, 0.25f, 0.25f, 0) * _timestep;

		(*color).r = (*color).r < 0 ? 0 : (*color).r;
		(*color).g = (*color).g < 0 ? 0 : (*color).g;
		(*color).b = (*color).b < 0 ? 0 : (*color).b;
		//(*color).a = (*color).a < 0 ? 0 : (*color).a;
	}
};

class AmbientBrightnessUp : public InputComponent {

	Colour* color;

public:
	AmbientBrightnessUp(Colour* _color, SDL_Keycode key) : color(_color), InputComponent(nullptr, key) {};
	void whenPressed(float _timestep){
		*color += Colour(0.25f, 0.25f, 0.25f, 0) * _timestep;

		(*color).r = (*color).r < 0 ? 0 : (*color).r;
		(*color).g = (*color).g < 0 ? 0 : (*color).g;
		(*color).b = (*color).b < 0 ? 0 : (*color).b;
		//(*color).a = (*color).a > 1 ? 1 : (*color).a;
	}
};