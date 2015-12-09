#include "GuiImage.h"
#include "Level.h"
#include "ModelManager.h"
#include "RenderableComponent.h"

GuiImage::GuiImage(Level* _level, std::string _textureName, Vec2 _screenPosition)
	: GuiElement(_level, _screenPosition)
{
	texture = ModelManager::getInstance()->GetTextureID(_textureName);

	ModelManager::getInstance()->CreatePlane("image", 1, 1);
	renderable = new RenderableComponent(ModelManager::getInstance()->GetModelID("image"), texture, this, new Material(0, 0, 0));
}

GuiImage::~GuiImage()
{

}

void GuiImage::Update(float _deltaTime)
{

}

void GuiImage::OnClick()
{

}

void GuiImage::OnHover()
{

}

bool GuiImage::CheckMouseCollision(int _x, int _y)
{
	return true;
}