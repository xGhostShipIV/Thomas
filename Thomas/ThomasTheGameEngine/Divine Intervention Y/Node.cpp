#include "Node.h"
#include <stdlib.h>
#include <dependencies\TinyXML\tinyxml2.h>

Node::Node(Level * _level, Vec3 _position, std::string fileName_) : GameObject(_level, _position)
{
	b = new Billboard(_level, _position);
	b->Scale(Vec3(0.6, 0.6, 0.6));
	addChild(b);
	fb = new Flipbook(b, 12, "Images/Animation/Star/slice0.png", 0.5f, false, Flipbook::PNG);
	fb->SetEffecctedByLight(false, false, false);
	elapsedTime = rand() % 5;

	levelFileName = fileName_;

	tinyxml2::XMLDocument doc;
	doc.LoadFile(levelFileName.c_str());

	tinyxml2::XMLElement * element = doc.RootElement();

	objectiveName = element->Attribute("name");
	par = element->FloatAttribute("par");
	description = element->GetText();
}


Node::~Node()
{
}

void Node::Update(float _deltaTime)
{
	GameObject::Update(_deltaTime);

	if (elapsedTime > 2.0f)
	{
		fb->Play();
		elapsedTime = 0.0f;
	}
	else elapsedTime += _deltaTime;
}

std::string Node::GetFileName()
{
	return levelFileName;
}