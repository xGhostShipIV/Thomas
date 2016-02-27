//Author: Nathan Senter
//Date: 2/26/2016

#pragma once

#include <GameObject.h>

class GalaxyMap : public GameObject
{
public:
	GalaxyMap(Level *);
	~GalaxyMap();

	void Update(float) override;

	void SetIsRotating(bool);
	bool IsRotating();
private:

	const int NUMBER_OF_NODES = 1;

	//2 planes so theyll both render when you rotate it around
	//Face-culling avoidance
	GameObject * plane1, * plane2;

	std::vector<GameObject *> nodes;

	//Gate for idle animation when title screen is up
	bool isRotating;
};

