#include "DrawComponent.h"

RenderableComponent::RenderableComponent(std::string _ID, GameObject* parent) : Component(parent){
	modelName = _ID;
}