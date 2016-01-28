//Author:	Mathieu Violette
//Date:		12/01/2015

#ifndef GUI_ELEMENT_H
#define GUI_ELEMENT_H

#include "..\Math\four_dimensions.hpp"
#include "GameObject.h"

class Level;
class RenderableComponent;

enum ScreenAnchor
{
	TOP_LEFT, TOP_CENTER, TOP_RIGHT,
	CENTER_LEFT, CENTER, CENTER_RIGHT,
	BOTTOM_LEFT, BOTTOM_CENTER, BOTTOM_RIGHT
};

class GuiElement : public GameObject
{
protected:
	bool isVisible;
	UINT32 texture;
	RenderableComponent *renderable;
	Vec2 guiScale;
public:

	GuiElement(Level* _level, Vec2 _screenPosition, ScreenAnchor anchor_ = ScreenAnchor::BOTTOM_LEFT);
	~GuiElement();

	virtual void Update(float _deltaTime) = 0;
	virtual void Draw();
	
	ScreenAnchor anchorPosition;

	bool IsVisible();
	void Show();
	void Hide();
	virtual bool CheckMouseCollision(int _x, int _y);
	virtual void Scale(Vec3 scale_) override;
};

#endif