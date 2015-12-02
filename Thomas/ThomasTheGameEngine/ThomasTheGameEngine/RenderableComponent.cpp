#include "RenderableComponent.h"
#include "ModelManager.h"
#include "Renderable.h"
#include "GameObject.h"

RenderableComponent::RenderableComponent(std::string _modelID, std::string _textureID, GameObject* _parent, Material * _mat) : Component(_parent, Component::ComponentType::Renderable){
	
	modelName = ModelManager::getInstance()->modelMap.find(_modelID)->second;
	textureName.push_back(ModelManager::getInstance()->textureMap.find(_textureID)->second);
	mat = _mat;
}

RenderableComponent::RenderableComponent(UINT32 _modelID, UINT32 _textureID, GameObject* _parent, Material * _mat) : Component(_parent, Component::ComponentType::Renderable)
{
	modelName = _modelID;
	textureName.push_back(_textureID);
	mat = _mat;
}

void RenderableComponent::DrawModel()
{
	if (ModelManager::getInstance()->render_mode == RENDER_MODE_OPENGL)
	{
		//something about uniforms

		static_cast<OpenGL_Renderable *>(ModelManager::getInstance()->getModel(modelName))->Draw(*parentObject, mat, textureName);
	}
}

void RenderableComponent::DrawUI()
{
	if (ModelManager::getInstance()->render_mode == RENDER_MODE_OPENGL)
	{
		static_cast<OpenGL_Renderable *>(ModelManager::getInstance()->getModel(modelName))->DrawUI(*parentObject, mat, textureName);
	}
}

void RenderableComponent::DrawWireframe()
{
	if (ModelManager::getInstance()->render_mode == RENDER_MODE_OPENGL)
		static_cast<OpenGL_Renderable *>(ModelManager::getInstance()->getModel(modelName))->DrawWireFrame(*parentObject);
}

void RenderableComponent::SetEffecctedByLight(bool _directional, bool _point, bool _spot)
{
	ModelManager::getInstance()->getModel(modelName)->isEffectedByLight = Vec3(_directional, _point, _spot);
}