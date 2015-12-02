#include "GuiElement.h"
#include "Level.h"
#include "RenderableComponent.h"

GuiElement::GuiElement(Level* _level, Vec2 _screenPosition) : GameObject(nullptr, Vec3(_screenPosition.x, _screenPosition.y, 0))
{
	isVisible = true;

	//Register with level
	_level->guiElements.push_back(this);

	//For some reason Text is upside down...
	Rotate(Quat(3.141592654f, Vec3::BasisZ()));
};

GuiElement::~GuiElement()
{
	if (renderable)
		delete renderable;
}

void GuiElement::Draw()
{
	if (renderable)
		renderable->DrawUI();
}

bool GuiElement::IsVisible() { return isVisible; }

void GuiElement::Show() { isVisible = true; }

void GuiElement::Hide() { isVisible = false; }