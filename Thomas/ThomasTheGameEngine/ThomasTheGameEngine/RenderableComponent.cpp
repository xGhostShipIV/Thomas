#include "RenderableComponent.h"
#include "ModelManager.h"
#include "Renderable.h"
#include "GameObject.h"

RenderableComponent::RenderableComponent(std::string _modelID, std::string _textureID, GameObject* _parent, Material * _mat) : Component(_parent, Component::ComponentType::Renderable){
	modelName = _modelID;
	textureName = _textureID;
	mat = _mat;
}

void RenderableComponent::DrawModel()
{
	if (ModelManager::getInstance()->render_mode == RENDER_MODE_OPENGL)
	{
		//something about uniforms

		static_cast<OpenGL_Renderable *>(ModelManager::getInstance()->getModel(modelName))->Draw(parentObject->GetTransform(), mat, ModelManager::getInstance()->getTexture(textureName));
	}
}

void RenderableComponent::DrawWireframe()
{
	if (ModelManager::getInstance()->render_mode == RENDER_MODE_OPENGL)
		static_cast<OpenGL_Renderable *>(ModelManager::getInstance()->getModel(modelName))->DrawWireFrame(parentObject->GetTransform());
}