#include "Label.h"
#include <SDL_image.h>
#include "ModelManager.h"
#include "Level.h"
#include "RenderableComponent.h"

TextSprite* txtSprite;

Label::Label(Level *_level, std::string _text, Vec2 _screenPosition, TTF_Font* _font, Colour _textColour) 
	: GuiElement(_level, _screenPosition), font(_font), text(_text), textColour(_textColour)
{
	//create a texture based off text
	txtSprite = new TextSprite(_text, _font, _textColour);
	texture = txtSprite->mapAddress;

	scale = Vec3(txtSprite->width * 0.35f, txtSprite->height * 0.35f, 1);

	//create square model to draw on
	ModelManager::getInstance()->CreateSquare("label", 0.01f, 0.01f);
	renderable = new RenderableComponent(ModelManager::getInstance()->GetModelID("label"), texture, this, new Material(0, 0, 0));
}

Label::~Label()
{

}

void Label::Update(float _deltaTime){}

//void Label::Draw()
//{
//	
//}

void Label::OnClick(){}

void Label::OnHover(){}

bool Label::CheckMouseCollision(int _x, int _y)
{
	//Fix later
	return true;
}

void Label::SetTextColor(Colour _color)
{
	textColour = _color;

	txtSprite->ReCreateTexture(text, font, textColour);
}

void Label::SetText(std::string _text)
{
	text = _text;

	txtSprite->ReCreateTexture(text, font, textColour);
}
