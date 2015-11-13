#include "Material.h"


Material::Material(float _ambient, float _diffuse, float _specular)
{
	material = Vec3(_ambient, _diffuse, _specular);
}

Material::Material(Material_Prefab _preDefinedMaterial)
{
	//I Dont know actual values so this is blank for now
	switch (_preDefinedMaterial)
	{
	case MATTE:
		break;
	case METALIC:
		break;
	default:
		break;
	}
}


Material::~Material()
{
}
