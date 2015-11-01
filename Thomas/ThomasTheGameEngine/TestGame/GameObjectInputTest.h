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