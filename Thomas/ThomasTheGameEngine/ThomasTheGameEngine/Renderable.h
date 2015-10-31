#include "Component.h"
#include <vector>
#include "../Math/four_dimensions.hpp"

class Transform;


class Renderable
{
	friend class ModelManager;
public:
	~Renderable(){};

	std::vector<Vec3> vertex;
	std::vector<unsigned int> edge;
	std::vector<unsigned int> face;
	std::vector<Vec3> normal;

	virtual void Draw(Transform) = 0;
	virtual void DrawWireFrame(Transform) = 0;

private:

protected:
	unsigned int offsetVertex;

	Renderable(){};
};

class OpenGL_Renderable : public Renderable {
public:
	void Draw(Transform) override;
	void DrawWireFrame(Transform) override;
};
