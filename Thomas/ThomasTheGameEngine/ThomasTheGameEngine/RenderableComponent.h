#pragma once
#include "Component.h"
#include <string>

/*
	A component that contains all the graphical information that can be
	associated with a gameObject. This component helps to ensure that
	models draw themselves and are being drawn based on the desired
	graphics engine.
*/
class RenderableComponent : public Component {

public:
	//An identifier string that will be used to find
	//the model information from the modelManager
	std::string modelName, textureName;

	RenderableComponent(std::string _modelID, std::string _textureID, GameObject* _parent);

	//Draws a filled in model
	void DrawModel();

	//Draws the wireframe of the model
	void DrawWireframe();
};