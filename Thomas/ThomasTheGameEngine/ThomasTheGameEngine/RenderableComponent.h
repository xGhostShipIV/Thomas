#pragma once
#include "Component.h"
#include <string>
#include "Material.h"
#include <vector>

typedef unsigned int UINT32;

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
	UINT32 modelName;
	std::vector<UINT32> textureName;

	Material * mat;

	RenderableComponent(std::string _modelID, std::string _textureID, GameObject* _parent, Material * mat = new Material(1.0f, 1.0f, 1.0f));
	RenderableComponent(UINT32 _modelID, UINT32 _textureID, GameObject* _parent, Material * mat = new Material(1.0f, 1.0f, 1.0f));

	//Draws a filled in model
	void DrawModel();

	//Draw UI to the screen
	void DrawUI();

	//Draws the wireframe of the model
	void DrawWireframe();

	void SetEffecctedByLight(bool _directional = true, bool _point = true, bool _spot = true);
};