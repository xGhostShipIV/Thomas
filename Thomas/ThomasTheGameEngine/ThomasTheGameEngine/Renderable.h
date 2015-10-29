#include "Component.h"
#include <vector>
#include "../Math/four_dimensions.hpp"
class Renderable : public Component
{
public:
	Renderable(GameObject * _go) : Component(_go){
	}

	~Renderable(){}

	std::vector<Vec3> vertices;
	std::vector<int> edges;

	virtual void Draw() = 0;
private:
	int offset;
	Vec4 colour;
};