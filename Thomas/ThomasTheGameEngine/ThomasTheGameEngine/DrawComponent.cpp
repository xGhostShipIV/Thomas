#include "DrawComponent.h"
#include "ModelManager.h"
#include "Renderable.h"
#include "GameObject.h"

RenderableComponent::RenderableComponent(std::string _ID, GameObject* parent) : Component(parent){
	modelName = _ID;
}

void RenderableComponent::DrawModel()
{
	if (ModelManager::getInstance()->render_mode == RENDER_MODE_OPENGL)
		static_cast<OpenGL_Renderable *>(ModelManager::getInstance()->getModel(modelName))->Draw(*(parentObject->transform));
}