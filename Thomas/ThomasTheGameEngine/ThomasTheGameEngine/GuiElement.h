//Author:	Mathieu Violette
//Date:		12/01/2015

#ifndef GUI_ELEMENT_H
#define GUI_ELEMENT_H

#include "..\Math\four_dimensions.hpp"
#include "GameObject.h"

class Level;
class RenderableComponent;

class GuiElement : public GameObject
{
protected:
	bool isVisible;
	RenderableComponent *renderable;
public:

	GuiElement(Level* _level, Vec2 _screenPosition);
	~GuiElement();

	virtual void Update(float _deltaTime) = 0;
	virtual void Draw();
	
	bool IsVisible();
	void Show();
	void Hide();
};

#endif