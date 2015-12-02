#include "../Math/four_dimensions.hpp"
#include "Colour.h"

class LightManager
{
public:
	struct DirectionalLight
	{
		Colour colour;
		Vec4 direction;
	};

	struct PointLight
	{
		Colour colour;
		Vec4 position;
	};

	struct SpotLight
	{
		Colour colour;
		Vec4 position, direction;
		float coneAngle;
	};
	
	~LightManager();

	//A static pointer to an instance of the manager
	static LightManager * instance;

	//Returns a pointer to a LightManager.
	static LightManager * getInstance(){
		if (!instance)instance = new LightManager();
		return instance;
	}

	//Input a Directional Light into Light array
	void InputDirectionalLight(Colour _color, Vec4 _direction);

	//Input a Point Light into Light array
	void InputPointLight(Colour _color, Vec4 _position);

	//Input a Spot Light into Light array
	void InputSpotLight(Colour _color, Vec4 _position, Vec4 _direction, float _coneAngle);

	//Pushes Lights to Shaders. Should be called After lighting arrays have been built and before draw calls.
	void PushLights();

private:
	LightManager();

	void ResetDirectional();
	void ResetPoint();
	void ResetSpot();

	unsigned int directionalIndex, pointIndex, spotIndex;
	static const unsigned int DirectionalLength = 1, PointLength = 2, SpotLength = 2;
	DirectionalLight Directional[DirectionalLength];
	PointLight Point[PointLength];
	SpotLight Spot[SpotLength];

};