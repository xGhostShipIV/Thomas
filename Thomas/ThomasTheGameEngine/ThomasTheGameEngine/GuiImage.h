//Author:	Mathieu Violette
//Date:		12/03/2015

#ifndef GUI_IMAGE_H
#define GUI_IMAGE_H

#include "GuiElement.h"
#include <string>
#include "Texture.h"

class Level;

class GuiImage : public GuiElement
{
protected:
	UINT32 texture;
public:

	GuiImage(Level* _level, std::string _textureName, Vec2 _screenPosition);
	~GuiImage();
	virtual void Update(float _deltaTime) override;

	virtual void OnClick();
	virtual void OnHover();

	virtual bool CheckMouseCollision(int _x, int _y);
};

#endif