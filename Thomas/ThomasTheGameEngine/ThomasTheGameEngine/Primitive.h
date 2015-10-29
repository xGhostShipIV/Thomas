#pragma once
#include "Renderable.h"
class Primitive :
	public Renderable
{
	enum LevelOfDetail{
		LODHigh,
		LODMedium,
		LODLow
	};

public:
	Primitive(GameObject *);
	~Primitive();

	void CreateCuboid(float _l, float _w, float _h);
	void CreateSphere(float _r, LevelOfDetail _lod);
	void CreateCone(float _r, float _h);
	void CreateCylinder(float _r, float _h);
	void CreatePyramid(float _l, float _w, float _h);

	void Draw() override;

};

