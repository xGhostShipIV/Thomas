#include "GuiImage.h"
#include "Level.h"
#include "ModelManager.h"
#include "RenderableComponent.h"
#include "GameProperties.h"

GuiImage::GuiImage(Level* _level, std::string _textureName, Vec2 _screenPosition, ScreenAnchor anchor_)
: GuiElement(_level, _screenPosition, anchor_)
{
	texture = ModelManager::getInstance()->GetTextureID(_textureName);
	renderable = new RenderableComponent(ModelManager::getInstance()->GetModelID("GUI"), texture, this, new Material(0, 0, 0));
	
	//Adjust scale so image appears at 1:1 pixel size on the screen
	guiScale = Vec2(ModelManager::getInstance()->GetTextureWidth(texture) / (float)GameProperties::getInstance()->getVideoProperties()->screenWidth,
				 ModelManager::getInstance()->GetTextureHeight(texture) / (float)GameProperties::getInstance()->getVideoProperties()->screenHeight);
	scale = Vec3(guiScale.x, guiScale.y, 1);
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