#pragma once
#include <InputComponent.h>
#include <GameObject.h>

class GameObject_PosX : public InputComponent {

	GameObject* go;

public:
	GameObject_PosX(GameObject* _go) : go(_go), InputComponent(_go) {};
	void whenPressed(){
		go->Translate(Vec3(0.1f, 0, 0));
	}
};

class GameObject_NegX : public InputComponent {

	GameObject* go;

public:
	GameObject_NegX(GameObject* _go) : go(_go), InputComponent(_go) {};
	void whenPressed(){
		go->Translate(Vec3(-0.1f, 0, 0));
	}
};

class GameObject_ScaleUp : public InputComponent {

	GameObject* go;

public:
	GameObject_ScaleUp(GameObject* _go) : go(_go), InputComponent(_go) {};
	void whenPressed(){
		go->Scale(Vec3(1.1f, 1.1f, 1.1f));
	}
};

class GameObject_ScaleDown : public InputComponent {

	GameObject* go;

public:
	GameObject_ScaleDown(GameObject* _go) : go(_go), InputComponent(_go) {};
	void whenPressed(){
		go->Scale(Vec3(1/1.1f, 1/1.1f, 1/1.1f));
	}
};

class AmbientBrightnessDown : public InputComponent {

	Vec4* color;

public:
	AmbientBrightnessDown(Vec4* _color) : color(_color), InputComponent(nullptr) {};
	void whenPressed(){
		*color -= Vec4(0.01, 0.01, 0.01, 0);

		(*color).x = (*color).x < 0 ? 0 : (*color).x;
		(*color).y = (*color).y < 0 ? 0 : (*color).y;
		(*color).z = (*color).z < 0 ? 0 : (*color).z;
		(*color).w = (*color).w < 0 ? 0 : (*color).w;

	}
};

class AmbientBrightnessUp : public InputComponent {

	Vec4* color;

public:
	AmbientBrightnessUp(Vec4* _color) : color(_color), InputComponent(nullptr) {};
	void whenPressed(){
		*color += Vec4(0.01, 0.01, 0.01, 0);

		(*color).x = (*color).x > 1 ? 1 : (*color).x;
		(*color).y = (*color).y > 1 ? 1 : (*color).y;
		(*color).z = (*color).z > 1 ? 1 : (*color).z;
		(*color).w = (*color).w > 1 ? 1 : (*color).w;
	}
};