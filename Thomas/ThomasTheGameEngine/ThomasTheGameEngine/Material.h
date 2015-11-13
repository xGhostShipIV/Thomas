#pragma once

#include "../Math/four_dimensions.hpp"

#define MATERIAL_TYPE_MATTE Material_Prefab.Matte
#define MATERIAL_TYPE_METALIC Material_Prefab.Metalic

enum Material_Prefab{
	MATTE,
	METALIC
};

class Material
{
public:
	Material(float _ambient, float _diffuse, float _specular);
	Material(Material_Prefab _preDefinedMaterial);

	~Material();

	Vec3 material;
};

