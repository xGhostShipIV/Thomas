#pragma once

#include <GameObject.h>
#include <RenderableComponent.h>

class Planet : public GameObject
{
public:
	Planet(Level *, Vec3, std::string textName_);
	~Planet();

	void Update(float) override;
	Generic_RenderableComponent * renderer;
};