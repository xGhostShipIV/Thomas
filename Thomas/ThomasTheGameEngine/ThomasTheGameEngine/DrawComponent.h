#pragma once
#include "Component.h"
#include <string>

class RenderableComponent : public Component {
public:
	std::string modelName;
	RenderableComponent(std::string, GameObject*);
};