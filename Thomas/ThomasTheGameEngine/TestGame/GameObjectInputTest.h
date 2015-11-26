#pragma once
#include <InputComponent.h>
#include <GameObject.h>

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

	Vec4* color;

public:
	AmbientBrightnessDown(Vec4* _color, SDL_Keycode key) : color(_color), InputComponent(nullptr, key) {};
	void whenPressed(float _timestep){
		*color -= Vec4(0, 0.25f, 0.25f, 0.25f) * _timestep;

		(*color).x = (*color).x < 0.1f ? 0.1f : (*color).x;
		(*color).y = (*color).y < 0.1f ? 0.1f : (*color).y;
		(*color).z = (*color).z < 0.1f ? 0.1f : (*color).z;
		//(*color).w = (*color).w < 0 ? 0 : (*color).w;

	}
};

class AmbientBrightnessUp : public InputComponent {

	Vec4* color;

public:
	AmbientBrightnessUp(Vec4* _color, SDL_Keycode key) : color(_color), InputComponent(nullptr, key) {};
	void whenPressed(float _timestep){
		*color += Vec4(0, 0.25f, 0.25f, 0.25f) * _timestep;

		(*color).x = (*color).x > 1 ? 1 : (*color).x;
		(*color).y = (*color).y > 1 ? 1 : (*color).y;
		(*color).z = (*color).z > 1 ? 1 : (*color).z;
		//(*color).w = (*color).w > 1 ? 1 : (*color).w;
	}
};