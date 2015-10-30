#include "Component.h"
#include <vector>
#include "../Math/four_dimensions.hpp"


class Renderable
{
	friend class ModelManager;
public:
	~Renderable(){};

	std::vector<Vec3> vertex;
	std::vector<int> face;
	std::vector<Vec3> normal;

	virtual void Draw() = 0;

private:
	int offsetVertex;
	int offsetFace;

protected:
	Renderable(){};
};

class OpenGL_Renderable : public Renderable {
public:
	void Draw() override {}
};