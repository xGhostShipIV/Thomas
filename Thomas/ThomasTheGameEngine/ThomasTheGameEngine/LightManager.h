#include "../Math/four_dimensions.hpp"

class LightManager
{
public:
	struct DirectionalLight
	{
		Vec4 color, direction;
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

	//TODO: PointLight, SpotLight.

	//Pushes Lights to Shaders. Should be called After lighting arrays have been built and before draw calls.
	void PushLights();

private:
	LightManager();

	void ResetDirectional();

	unsigned int directionIndex;
	static const unsigned int DirectionLength = 2;
	DirectionalLight Directional[DirectionLength];

};