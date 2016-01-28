#include "GameObject.h"
#include <vector>
#include "../Math/four_dimensions.hpp"
#include "ModelManager.h"

class Texture;
class Material;
enum ScreenAnchor;

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

	struct Mesh
	{
		//Lists of all vertecies, edges, faces and normals
		std::vector<Vec3> vertex;
		std::vector<unsigned int> edge;
		std::vector<unsigned int> face;
		std::vector<Vec3> normal;
		std::vector<Vec3> faceNormal;
		std::vector<Vec2> textureMap;
		
		unsigned int offsetVertex;
	};

	std::vector<Mesh> meshes;
	Vec3 isEffectedByLight;

	virtual void Draw(GameObject&, Material *, std::vector<UINT32> _textureNames) = 0;
	virtual void DrawUI(GameObject&, Material *, std::vector<UINT32> _textureNames, ScreenAnchor anchor_) = 0;
	virtual void DrawWireFrame(GameObject&) = 0;

private:

protected:
	
	ModelManager::Draw_Mode drawMode;

	Renderable()
	{
		drawMode = ModelManager::Draw_Mode::CCW;
		isEffectedByLight = Vec3::One();
	};
};

/*
	A derived class that will override the draw methods to
	specify how OpenGL draws renderables
	*/
class OpenGL_Renderable : public Renderable {
public:
	void Draw(GameObject& parentTransform, Material * _mat, std::vector<UINT32> _textureNames) override;
	void DrawUI(GameObject&, Material *, std::vector<UINT32> _textureNames, ScreenAnchor anchor_) override;
	void DrawWireFrame(GameObject& parentTransform) override;
};
