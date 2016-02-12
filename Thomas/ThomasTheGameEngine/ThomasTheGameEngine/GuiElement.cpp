#include "GuiElement.h"
#include "Level.h"
#include "RenderableComponent.h"
#include "ModelManager.h"
#include "GameProperties.h"

GuiElement::GuiElement(Level* _level, Vec2 _screenPosition, ScreenAnchor anchor_) : GameObject(nullptr, Vec3(_screenPosition.x, _screenPosition.y, 0)),
	anchorPosition(anchor_)
{
	isVisible = true;
	drawPercent = 1;
	drawType = UI_DRAW_TYPE::NORMAL;

	//Register with level
	_level->guiElements.push_back(this);

	//For some reason Text is upside down...
	Rotate(Quat(3.141592654f, Vec3::BasisZ()));
	Rotate(Quat(3.141592654f, Vec3::BasisY()));

	ModelManager::getInstance()->CreatePlane("GUI", 2, 2);
};

GuiElement::~GuiElement()
{
	if (renderable)
		delete renderable;
}

void GuiElement::Draw()
{
	if (renderable)
		renderable->DrawUI(anchorPosition);
}

bool GuiElement::IsVisible() { return isVisible; }

void GuiElement::Show() { isVisible = true; }

void GuiElement::Hide() { isVisible = false; }

bool GuiElement::CheckMouseCollision(int _x, int _y)
{
	//Construct rectangle bounds of the button
	int rX, rY, rW, rH;
		
	rW = ModelManager::getInstance()->GetTextureWidth(texture) * scale.x / guiScale.x;
	rH = ModelManager::getInstance()->GetTextureHeight(texture) * scale.y / guiScale.y;

	rX = position.x - rW / 2.0f;
	rY = position.y - rH / 2.0f;

	//Adjust for anchor position
	switch (anchorPosition)
	{
	case ScreenAnchor::TOP_LEFT:
		rY += GameProperties::getInstance()->getVideoProperties()->screenHeight;
		break;
	case ScreenAnchor::TOP_CENTER:
		rX += GameProperties::getInstance()->getVideoProperties()->screenWidth / 2.0f;
		rY += GameProperties::getInstance()->getVideoProperties()->screenHeight;
		break;
	case ScreenAnchor::TOP_RIGHT:
		rX += GameProperties::getInstance()->getVideoProperties()->screenWidth;
		rY += GameProperties::getInstance()->getVideoProperties()->screenHeight;
		break;
	case ScreenAnchor::CENTER_LEFT:
		rY += GameProperties::getInstance()->getVideoProperties()->screenHeight / 2.0f;
		break;
	case ScreenAnchor::CENTER:
		rX += GameProperties::getInstance()->getVideoProperties()->screenWidth / 2.0f;
		rY += GameProperties::getInstance()->getVideoProperties()->screenHeight / 2.0f;
		break;
	case ScreenAnchor::CENTER_RIGHT:
		rX += GameProperties::getInstance()->getVideoProperties()->screenWidth;
		rY += GameProperties::getInstance()->getVideoProperties()->screenHeight / 2.0f;
		break;
	case ScreenAnchor::BOTTOM_LEFT:
		//Default, do nothing
		break;
	case ScreenAnchor::BOTTOM_CENTER:
		rX += GameProperties::getInstance()->getVideoProperties()->screenWidth / 2.0f;
		break;
	case ScreenAnchor::BOTTOM_RIGHT:
		rX += GameProperties::getInstance()->getVideoProperties()->screenWidth;
		break;
	}

	//Check if x & y are contained within bounds
	return (_x >= rX &&
			_x <= rX + rW &&
			_y >= rY &&
			_y <= rY + rH);
}

void GuiElement::Scale(Vec3 scale_)
{
	scale = Vec3(scale.x / guiScale.x, scale.y / guiScale.y, scale.z);

	scale = Vec3(guiScale.x * scale.x * scale_.x, guiScale.y * scale.y * scale_.y, scale.z * scale_.z);

	for (auto it = childObjects.begin(); it != childObjects.end(); it++){
		(*it)->Scale(scale_);
	}
}