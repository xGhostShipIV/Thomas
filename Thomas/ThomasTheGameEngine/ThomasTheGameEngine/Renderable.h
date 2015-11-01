#include "GameObject.h"
#include <vector>
#include "../Math/four_dimensions.hpp"

/*
	An abstract class that contains all information a renderable object
	would have. The draw method is abstract so that a concrete class can 
	be made to specify how its draw.
*/

class Renderable
{
	friend class ModelManager;
public:
	~Renderable(){};

	//Lists of all vertecies, edges, faces and normals
	std::vector<Vec3> vertex;
	std::vector<unsigned int> edge;
	std::vector<unsigned int> face;
	std::vector<Vec3> normal;

	virtual void Draw(GameObject&) = 0;
	virtual void DrawWireFrame(GameObject&) = 0;

private:

protected:
	unsigned int offsetVertex;

	Renderable(){};
};

/*
	A derived class that will override the draw methods to
	specify how OpenGL draws renderables
*/
class OpenGL_Renderable : public Renderable {
public:
	void Draw(GameObject&) override;
	void DrawWireFrame(GameObject&) override;
};
