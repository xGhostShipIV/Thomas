#include "../Math/four_dimensions.hpp"

class LightManager
{
public:
	struct DirectionalLight
	{
		Vec4 color, direction;
	};

	struct PointLight
	{
		Vec4 color, position;
		float radius;
	};

	struct SpotLight
	{
		Vec4 color, position, direction;
		float radius, coneAngle;
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
	void InputDirectionalLight(Vec4 _color, Vec4 _direction);

	//Input a Point Light into Light array
	void InputPointLight(Vec4 _color, Vec4 _position, float _radius);

	//Input a Spot Light into Light array
	void InputSpotLight(Vec4 _color, Vec4 _position, Vec4 _direction, float _radius, float _coneAngle);

	//Pushes Lights to Shaders. Should be called After lighting arrays have been built and before draw calls.
	void PushLights();

private:
	LightManager();

	void ResetDirectional();
	void ResetPoint();
	void ResetSpot();

	unsigned int directionalIndex, pointIndex, spotIndex;
	static const unsigned int DirectionalLength = 2, PointLength = 4, SpotLength = 4;
	DirectionalLight Directional[DirectionalLength];
	PointLight Point[PointLength];
	SpotLight Spot[SpotLength];

};